#include "../renderer.h"

#include "../glass_parts.h"
#include "../image.h"
#include "../light.h"
#include "../solid_parts.h"
#include "heragl.h"

namespace
{

template <typename T>
concept Part = requires(T t) {
  { t.tex } -> std::same_as<hera::Texture&>;
  { t.mat } -> std::same_as<ares::dmatrix&>;
};

template <typename T>
concept Face = requires(T t) {
  { t.norm } -> std::same_as<ares::fvec3&>;
  { t.is_quad } -> std::same_as<bool&>;
};

/**
 * @brief Render face
 * @tparam P Part type
 * @tparam F Face type
 * @param part Part that the face belongs to
 * @param face Face to render
 * @param vertices Face vertices
 */
template <Part P, Face F>
void render_face(const P& part, const F& face, std::span<const hera::Vertex> vertices);

} // namespace

namespace hera
{

Renderer::Renderer()
{
  _filter[static_cast<int>(Texture::Mag::Nearest)] = GL_NEAREST;
  _filter[static_cast<int>(Texture::Mag::Linear)] = GL_LINEAR;
  _filter[static_cast<int>(Texture::Min::Nearest_mipmap_nearest)] = GL_NEAREST_MIPMAP_NEAREST;
  _filter[static_cast<int>(Texture::Min::Linear_mipmap_nearest)] = GL_LINEAR_MIPMAP_NEAREST;
  _filter[static_cast<int>(Texture::Min::Nearest_mipmap_linear)] = GL_NEAREST_MIPMAP_LINEAR;
  _filter[static_cast<int>(Texture::Min::Linear_mipmap_linear)] = GL_LINEAR_MIPMAP_LINEAR;

  _blend[Blend::Factor::One] = GL_ONE;
  _blend[Blend::Factor::Src_alpha] = GL_SRC_ALPHA;
  _blend[Blend::Factor::One_minus_src_alpha] = GL_ONE_MINUS_SRC_ALPHA;
  _blend[Blend::Factor::Dst_alpha] = GL_DST_ALPHA;
  _blend[Blend::Factor::One_minus_dst_alpha] = GL_ONE_MINUS_DST_ALPHA;

  _lights[0] = GL_LIGHT0;
  _lights[1] = GL_LIGHT1;
  _lights[2] = GL_LIGHT2;
  _lights[3] = GL_LIGHT3;
  _lights[4] = GL_LIGHT4;
  _lights[5] = GL_LIGHT5;
  _lights[6] = GL_LIGHT6;
  _lights[7] = GL_LIGHT7;
}



void Renderer::basic_scene_setup() const
{
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 1);
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}



void Renderer::basic_start_scene() const
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
}



void Renderer::set_viewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
  _viewport[Vp::pos_x] = x;
  _viewport[Vp::pos_y] = y;
  _viewport[Vp::width] = width;
  _viewport[Vp::height] = height;
  glViewport(x, y, width, height);
}



void Renderer::set_perspective(
  bool push_mvp, double fov, double aspect, double znear, double zfar) const
{
  // Select the projection matrix, store it if required and reset it
  glMatrixMode(GL_PROJECTION);
  if (push_mvp)
  {
    glPushMatrix();
  }
  glLoadIdentity();

  // Set a perspective projection matrix
  gluPerspective(fov, aspect, znear, zfar);

  // Select the modelview matrix, store it if required and reset it
  glMatrixMode(GL_MODELVIEW);
  if (push_mvp)
  {
    glPushMatrix();
  }
  glLoadIdentity();
}



const ares::dvec3 Renderer::un_project(double winx, double winy, double winz) const
{
  ares::dvec3 pos;
  glGetDoublev(GL_MODELVIEW_MATRIX, _mx1.data);
  glGetDoublev(GL_PROJECTION_MATRIX, _mx2.data);
  const int revy = _viewport[Vp::height] - winy - 1;
  gluUnProject(winx, revy, winz, _mx1.data, _mx2.data, _viewport, &pos.x, &pos.y, &pos.z);
  return pos;
}



void Renderer::look_at(
  const ares::dvec3& eye, const ares::dvec3& center, const ares::dvec3& up) const
{
  gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}



Texture Renderer::create_texture(const Image& img, Texture::Min min, Texture::Mag mag) const
{
  GLuint tex = 0;
  glGenTextures(1, &tex);

  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter[static_cast<int>(min)]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter[static_cast<int>(mag)]);

  if (Texture::Min::Nearest == min || Texture::Min::Linear == min)
  {
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      img.has_alpha ? GL_RGBA : GL_RGB,
      img.width,
      img.height,
      0,
      img.has_alpha ? GL_RGBA : GL_RGB,
      GL_UNSIGNED_BYTE,
      img.data());
  }
  else
  {
    gluBuild2DMipmaps(
      GL_TEXTURE_2D,
      img.has_alpha ? GL_RGBA : GL_RGB,
      img.width,
      img.height,
      img.has_alpha ? GL_RGBA : GL_RGB,
      GL_UNSIGNED_BYTE,
      img.data());
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  return {.id = static_cast<int32_t>(tex)};
}



void Renderer::render_parts(const Solid_parts& solids, const Glass_parts& glassy)
{
  for (const auto [part, face, vertices] : solids)
  {
    render_face(part, face, vertices);
  }

  glEnable(GL_BLEND);
  for (const auto [part, face, vertices] : glassy)
  {
    glBlendFunc(_blend[part.blend.src], _blend[part.blend.dst]);
    render_face(part, face, vertices);
  }
  glDisable(GL_BLEND);
}



constexpr int32_t Renderer::max_lights() const
{
  return static_cast<int32_t>(_lights.max_size());
}



void Renderer::use_lighting(bool enable) const
{
  if (enable)
  {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
  }
  else
  {
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
  }
}



bool Renderer::add_light(Light& light)
{
  if (0 == _light_count)
  {
    // set default material values for all lighting effects
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    const auto specular = fColor{.r = 1, .g = 1, .b = 1, .a = 1}.rgba();
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.data());
    const auto emission = fColor{.r = 0, .g = 0, .b = 0, .a = 1}.rgba();
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission.data());
  }

  const bool result = _light_count < max_lights();
  _light_count += result;
  light.id = _light_count - 1;

  const auto ambient = light.ambient.rgba();
  glLightfv(static_cast<GLenum>(_lights[light.id]), GL_AMBIENT, ambient.data());
  const auto diffuse = light.diffuse.rgba();
  glLightfv(static_cast<GLenum>(_lights[light.id]), GL_DIFFUSE, diffuse.data());
  const auto specular = light.specular.rgba();
  glLightfv(static_cast<GLenum>(_lights[light.id]), GL_SPECULAR, specular.data());
  return result;
}



void Renderer::set_light(const Light& light) const
{
  const auto pos = light.pos.xyzw();
  glLightfv(static_cast<GLenum>(_lights[light.id]), GL_POSITION, pos.data());
  glEnable(static_cast<GLenum>(_lights[light.id]));
}



void Renderer::unset_light(const Light& light) const
{
  glDisable(static_cast<GLenum>(_lights[light.id]));
}

} // namespace hera

namespace
{

template <Part P, Face F>
void render_face(const P& part, const F& face, std::span<const hera::Vertex> vertices)
{
  // save current matrix and set part matrix
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixd(part.mat.data);

  glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(part.tex.id));

  // render face
  glBegin(face.is_quad ? GL_QUADS : GL_TRIANGLES);
  glNormal3f(face.norm.x, face.norm.y, face.norm.z);
  for (const auto& v : vertices)
  {
    glTexCoord2d(v.tex.x, v.tex.y);
    glColor4ub(v.color.r, v.color.g, v.color.b, v.color.a);
    glVertex3d(v.pos.x, v.pos.y, v.pos.z);
  }
  glEnd();

  // restore original matrix
  glPopMatrix();
}

} // namespace
