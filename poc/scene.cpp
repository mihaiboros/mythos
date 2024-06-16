#include "scene.h"

#include <hera/image.h>
#include <hera/opengl/light_gl.h>
#include <hera/opengl/model_gl.h>
#include <hera/opengl/sysgl.h>
#include <hera/opengl/texture_gl.h>

namespace
{

/**
 * @brief Make triangle model
 * @return hera::Model Triangle model
 */
hera::tModel make_tris();

/**
 * @brief Make quad model
 * @return hera::Model Quad model
 */
hera::qModel make_quads();

/**
 * @brief Renders simple colored models
 * @param tris Triangle model
 * @param quads Quad model
 */
void render_simple_models(const hera::tModel& tris, const hera::qModel& quads);

} // namespace



namespace poc
{

using hera::Key;

void Scene::init(int32_t width, int32_t height)
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 0.5);
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
  m_quads = {.cs = {.o = {.z = -5}},
    .faces = {
      {.normal = {.z = 1},
        .vertices = {hera::Vertex{.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},
          {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},
          {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 0}},
          {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 0}}}},

      {.normal = {.z = -1},
        .vertices = {hera::Vertex{.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 1}},
          {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},
          {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}},
          {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 1}}}},

      {.normal = {.y = 1},
        .vertices = {hera::Vertex{.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}},
          {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 1}},
          {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 1}},
          {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}}}},

      {.normal = {.y = -1},
        .vertices = {hera::Vertex{.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 0}},
          {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 0}},
          {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},
          {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}}}},

      {.normal = {.x = 1},
        .vertices = {hera::Vertex{.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 1}},
          {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},
          {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 0}},
          {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}}}},

      {.normal = {.x = -1},
        .vertices = {hera::Vertex{.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 1}},
          {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},
          {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 0}},
          {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}}}}}};

  hera::Image img;
  img.load("resources/4_store.bmp");
  m_tex[0] = hera::make_texture(img, hera::Filter::Nearest, hera::Filter::Nearest);
  m_tex[1] = hera::make_texture(img, hera::Filter::Linear, hera::Filter::Linear);
  m_tex[2] = hera::make_texture(img, hera::Filter::Linear, hera::Filter::Linear_mipmap_nearest);

  m_light = {.pos = {.z = 2},
    .ambient = {.r = 0.3, .g = 0.3, .b = 0.3, .a = 1},
    .diffuse = {.r = 1, .g = 1, .b = 1, .a = 1}};

  hera::setup_light(m_light, hera::Light_id::Light1);
  hera::enable_light(hera::Light_id::Light1);
}



void Scene::handle_keys(const hera::Keymap& keys)
{
  if (!keys[Key::L])
  {
    m_lkey = false;
  }
  else if (!m_lkey)
  {
    m_lkey = true;
    m_has_light = !m_has_light;
    if (!m_has_light)
    {
      glDisable(GL_LIGHTING);
    }
    else
    {
      glEnable(GL_LIGHTING);
    }
  }

  if (!keys[Key::F])
  {
    m_fkey = false;
  }
  else if (!m_fkey)
  {
    m_fkey = true;
    m_idx = m_idx >= 2 ? 0 : m_idx + 1;
  }

  if (keys[Key::Pgdn])
  {
    m_zp -= 0.02;
  }
  if (keys[Key::Pgup])
  {
    m_zp += 0.02;
  }
  if (keys[Key::Up])
  {
    m_xs -= 0.01;
  }
  if (keys[Key::Down])
  {
    m_xs += 0.01;
  }
  if (keys[Key::Right])
  {
    m_ys += 0.01;
  }
  if (keys[Key::Left])
  {
    m_ys -= 0.01;
  }
}



void Scene::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  hera::bind_texture(m_tex[m_idx]);
  m_quads.cs.o.z = m_zp;
  hera::render_textured(m_quads, m_xr, m_yr, 0);

  m_xr += m_xs;
  m_yr += m_ys;
}

} // namespace poc



namespace
{

hera::tModel make_tris()
{
  return {.cs = {.o = {.x = -1.5, .z = -6}},
    .faces = {{.vertices = {hera::Vertex{.pos = {.y = 1}, .color = {.r = 255}},
                 {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.g = 255}},
                 {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.b = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.y = 1}, .color = {.r = 255}},
         {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.b = 255}},
         {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.g = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.y = 1}, .color = {.r = 255}},
         {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.g = 255}},
         {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.b = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.y = 1}, .color = {.r = 255}},
         {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.b = 255}},
         {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.g = 255}}}}}};
}



hera::qModel make_quads()
{
  return {.cs = {.o = {.x = 1.5, .z = -7}},
    .faces = {{.vertices = {hera::Vertex{.pos = {.x = 1, .y = 1, .z = -1}, .color = {.g = 255}},
                 {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.g = 255}},
                 {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.g = 255}},
                 {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.g = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128}},
         {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128}},
         {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128}},
         {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128}}}},

      {.vertices = {hera::Vertex{.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255}},
         {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 255}},
         {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255}},
         {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255}},
         {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255}},
         {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255}},
         {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.x = -1, .y = 1, .z = 1}, .color = {.b = 255}},
         {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.b = 255}},
         {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.b = 255}},
         {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.b = 255}}}},

      {.vertices = {hera::Vertex{.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .b = 255}},
         {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255, .b = 255}},
         {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .b = 255}},
         {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .b = 255}}}}}};
  return {};
}



void render_simple_models(const hera::tModel& tris, const hera::qModel& quads)
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
