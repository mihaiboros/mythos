#include "scene.h"

#include <hera/camera.h>
#include <hera/engine.h>
#include <hera/image.h>
#include <hera/opengl/forge.h>
#include <hera/opengl/heragl.h>
#include <hera/opengl/light_gl.h>
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



Scene::Scene() : _renderer(std::make_unique<Renderer>())
{
}



Scene::~Scene() = default;



void Scene::init(int32_t width, int32_t height)
{
  hera::engine.renderer.basic_scene_setup();
  resize(width, height);
}



void Scene::resize(int32_t width, int32_t height)
{
  hera::engine.renderer.set_viewport(0, 0, width, height);
  const double aspect = double(width) / height;
  hera::engine.renderer.set_perspective(false, 45, aspect, 0.1, 100);
  _camera.set_window_center(width / 2, height / 2);
  _camera.set_perspective(45, aspect, 0.1, 100);
}



void Scene::mouse_move(int x, int y)
{
  hera::engine.point_camera(_camera, x, y);
}



void Scene::load()
{
  _quads = {.cs = {.origin = {.z = -5}},
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

  //_quads = make_quads();
  //_tris = make_tris();

  hera::Image img;
  img.load("resources/stained.png");
  _quads.tex = hera::forge::texture(img, hera::Filter::Linear, hera::Filter::Linear_mipmap_nearest);

  _light = {.pos = {.z = 2},
    .ambient = {.r = 0.3, .g = 0.3, .b = 0.3, .a = 1},
    .diffuse = {.r = 1, .g = 1, .b = 1, .a = 1}};

  hera::setup_light(_light, hera::Light_id::Light1);
  hera::enable_light(hera::Light_id::Light1);

  glColor4f(1, 1, 1, 0.5f);
  _renderer->world.set_blend_factors(hera::Blend::Src_alpha, hera::Blend::One_minus_src_alpha);
}



void Scene::handle_keys(hera::Keymap& keys)
{
  if (!keys.is_pressed(Key::L))
  {
    _lkey = false;
  }
  else if (!_lkey)
  {
    _lkey = true;
    _has_light = !_has_light;
    if (_has_light)
    {
      glEnable(GL_LIGHTING);
    }
    else
    {
      glDisable(GL_LIGHTING);
    }
  }

  if (!keys.is_pressed(Key::B))
  {
    _bkey = false;
  }
  else if (!_bkey)
  {
    _bkey = true;
    _has_blend = !_has_blend;
    if (_has_blend)
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

  if (keys.is_pressed(Key::Pgdn))
  {
    _zp -= 0.01;
  }
  if (keys.is_pressed(Key::Pgup))
  {
    _zp += 0.01;
  }
  if (keys.is_pressed(Key::Up))
  {
    _xs -= 0.005;
    keys.release(Key::Up);
  }
  if (keys.is_pressed(Key::Down))
  {
    _xs += 0.005;
    keys.release(Key::Down);
  }
  if (keys.is_pressed(Key::Right))
  {
    _ys += 0.005;
    keys.release(Key::Right);
  }
  if (keys.is_pressed(Key::Left))
  {
    _ys -= 0.005;
    keys.release(Key::Left);
  }

  const double move_speed = 0.005;
  if (keys.is_pressed(Key::E))
  {
    _camera.advance(move_speed);
  }

  if (keys.is_pressed(Key::D))
  {
    _camera.advance(-move_speed);
  }

  if (keys.is_pressed(Key::S))
  {
    _camera.strafe(-move_speed);
  }

  if (keys.is_pressed(Key::F))
  {
    _camera.strafe(move_speed);
  }

  if (keys.is_pressed(Key::R))
  {
    _camera.ascend(move_speed);
  }

  if (keys.is_pressed(Key::C))
  {
    _camera.ascend(-move_speed);
  }

  const double roll_speed = 0.001;
  if (keys.is_pressed(Key::Q))
  {
    _camera.roll(-roll_speed);
  }

  if (keys.is_pressed(Key::W))
  {
    _camera.roll(roll_speed);
  }
}



void Scene::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  hera::engine.renderer.look_at(
    _camera.position(), _camera.position() + _camera.cs().x_axis, _camera.cs().y_axis);

  //_quads.cs.origin.z = _zp;
  //_renderer->world.render({}, std::initializer_list<const hera::Model>{_quads});

  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //_quads.bind_texture();
  //_quads.render_textured(_xr, _yr, 0);

  //_xr += _xs;
  //_yr += _ys;

  // render_simple_models(_tris, _quads);


  glBegin(GL_QUADS);
  glVertex3d(-0.5, -0.5, -3);
  glVertex3d(-0.5, 0.5, -3);
  glVertex3d(0.5, 0.5, -3);
  glVertex3d(0.5, -0.5, -3);
  glEnd();
}

} // namespace poc



namespace
{

hera::Model make_tris()
{
  return {.cs = {.origin = {.x = -1.5, .z = -6}},
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
  return {.cs = {.origin = {.x = 1.5, .z = -7}},
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
