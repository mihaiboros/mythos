#include "scene.h"

#include <hera/image.h>
#include <hera/opengl/model_gl.h>
#include <hera/opengl/sysgl.h>
#include <hera/opengl/texture_gl.h>

namespace
{

/**
 * @brief Make triangle model
 * @return hera::Model Triangle model
 */
hera::Model make_tris();

/**
 * @brief Make quad model
 * @return hera::Model Quad model
 */
hera::Model make_quads();

/**
 * @brief Renders simple colored models
 * @param tris Triangle model
 * @param quads Quad model
 */
void render_simple_models(const hera::Model& tris, const hera::Model& quads);

} // namespace



namespace poc
{

void Scene::init(int32_t width, int32_t height)
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 0);
  glClearDepth(1);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  resize(width, height);
}



void Scene::resize(int32_t width, int32_t height)
{
  glViewport(0, 0, width, height > 0 ? height : 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, static_cast<double>(width) / height, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void Scene::load()
{
  m_quads = {.has_quads = true,
    .cs = {.o = {.z = -5}},
    .vertices = {{.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 0}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 0}},

      {.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 1}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},
      {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 1}},

      {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 1}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 1}},
      {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},

      {.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 0}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 0}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},

      {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 1}},
      {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 0}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},

      {.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 1}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 0}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}}}};

  hera::Image img;
  img.load("resources/4_store.bmp");
  m_tex_id = hera::make_texture(img);

  m_amb = {.color = {.r = 128, .g = 128, .b = 128, .a = 255}, .is_ambiental = true};
  m_dif = {.pos = {.z = 2}, .color = {.r = 255, .g = 255, .b = 255, .a = 255}};
}



void Scene::draw()
{
  static double xr = 0;
  static double yr = 0;
  static double zr = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  hera::bind_texture(m_tex_id);
  hera::render_textured(m_quads, xr, yr, zr);

  xr += 0.3;
  yr += 0.2;
  zr += 0.4;
}

} // namespace poc



namespace
{

hera::Model make_tris()
{
  return {.cs = {.o = {.x = -1.5, .z = -6}},
    .vertices = {{.pos = {.y = 1}, .color = {.r = 255}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.g = 255}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.b = 255}},

      {.pos = {.y = 1}, .color = {.r = 255}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.b = 255}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.g = 255}},

      {.pos = {.y = 1}, .color = {.r = 255}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.g = 255}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.b = 255}},

      {.pos = {.y = 1}, .color = {.r = 255}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.b = 255}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.g = 255}}}};
}



hera::Model make_quads()
{
  return {.has_quads = true,
    .cs = {.o = {.x = 1.5, .z = -7}},
    .vertices = {{.pos = {.x = 1, .y = 1, .z = -1}, .color = {.g = 255}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.g = 255}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.g = 255}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.g = 255}},

      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128}},

      {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 255}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255}},

      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255}},
      {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255}},

      {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.b = 255}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.b = 255}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.b = 255}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.b = 255}},

      {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .b = 255}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255, .b = 255}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .b = 255}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .b = 255}}}};
}



void render_simple_models(const hera::Model& tris, const hera::Model& quads)
{
  static double tr{0};
  static double qr{0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  hera::render_colored(tris, 0, tr, 0);
  hera::render_colored(quads, qr, qr, qr);

  tr += 0.2;
  qr -= 0.15;
}

} // namespace
