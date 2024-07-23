#include "scene.h"

#include <hera/image.h>
#include <hera/opengl/forge.h>
#include <hera/opengl/light_gl.h>
#include <hera/opengl/sysgl.h>
#include <hera/opengl/world.h>

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

using hera::Key;

struct Scene::Renderer
{
  hera::World world;
};



Scene::Scene() : m_renderer(std::make_unique<Renderer>())
{
}



Scene::~Scene() = default;



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
      {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}}},
    .faces = {{.normal = {.z = 1}},
      {.normal = {.z = -1}},
      {.normal = {.y = 1}},
      {.normal = {.y = -1}},
      {.normal = {.x = 1}},
      {.normal = {.x = -1}}},
    .has_quads = true};

  // m_quads = make_quads();
  // m_tris = make_tris();

  hera::Image img;
  img.load("resources/stained.png");
  m_quads.tex =
    hera::forge::texture(img, hera::Filter::Linear, hera::Filter::Linear_mipmap_nearest);

  m_light = {.pos = {.z = 2},
    .ambient = {.r = 0.3, .g = 0.3, .b = 0.3, .a = 1},
    .diffuse = {.r = 1, .g = 1, .b = 1, .a = 1}};

  hera::setup_light(m_light, hera::Light_id::Light1);
  hera::enable_light(hera::Light_id::Light1);

  glColor4f(1, 1, 1, 0.5f);
  m_renderer->world.set_blend_factors(hera::Blend::Src_alpha, hera::Blend::One_minus_src_alpha);
}



void Scene::handle_keys(hera::Keymap& keys)
{
  if (!keys[Key::L])
  {
    m_lkey = false;
  }
  else if (!m_lkey)
  {
    m_lkey = true;
    m_has_light = !m_has_light;
    if (m_has_light)
    {
      glEnable(GL_LIGHTING);
    }
    else
    {
      glDisable(GL_LIGHTING);
    }
  }

  if (!keys[Key::B])
  {
    m_bkey = false;
  }
  else if (!m_bkey)
  {
    m_bkey = true;
    m_has_blend = !m_has_blend;
    if (m_has_blend)
    {
      glEnable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
    }
    else
    {
      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
    }
  }

  if (keys[Key::Pgdn])
  {
    m_zp -= 0.01;
  }
  if (keys[Key::Pgup])
  {
    m_zp += 0.01;
  }
  if (keys[Key::Up])
  {
    m_xs -= 0.005;
    keys[Key::Up] = false;
  }
  if (keys[Key::Down])
  {
    m_xs += 0.005;
    keys[Key::Down] = false;
  }
  if (keys[Key::Right])
  {
    m_ys += 0.005;
    keys[Key::Right] = false;
  }
  if (keys[Key::Left])
  {
    m_ys -= 0.005;
    keys[Key::Left] = false;
  }
}



void Scene::draw()
{
  m_quads.cs.o.z = m_zp;
  m_renderer->world.render({}, std::initializer_list<const hera::Model>{m_quads});

  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //  m_quads.bind_texture();
  //  m_quads.render_textured(m_xr, m_yr, 0);

  m_xr += m_xs;
  m_yr += m_ys;

  // render_simple_models(m_tris, m_quads);
}

} // namespace poc



namespace
{

hera::Model make_tris()
{
  return {.cs = {.o = {.x = -1.5, .z = -6}},
    .vertices = {{.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}},

      {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},

      {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},

      {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}}},
    .faces = {{}, {}, {}, {}}};
}



hera::Model make_quads()
{
  return {.cs = {.o = {.x = 1.5, .z = -7}},
    .vertices = {{.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}},

      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128, .b = 0}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128, .b = 0}},

      {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},

      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},
      {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},

      {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}},
      {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},
      {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},
      {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}},

      {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .g = 0, .b = 255}},
      {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255, .g = 0, .b = 255}},
      {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 0, .b = 255}},
      {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 0, .b = 255}}},
    .faces = {{}, {}, {}, {}, {}, {}},
    .has_quads = true};
}



void render_simple_models(const hera::Model& tris, const hera::Model& quads)
{
  static double tr{0};
  static double qr{0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  tris.render_colored(0, tr, 0);
  quads.render_colored(qr, qr, qr);

  tr += 0.05;
  qr -= 0.03;
}

} // namespace
