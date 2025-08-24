#include "scene.h"

#include <ares/matrix.h>
#include <hera/camera.h>
#include <hera/engine.h>
#include <hera/image.h>
#include <hera/opengl/heragl.h>
#include <hera/opengl/light_gl.h>

namespace
{

/**
 * @brief Add a colored piramid
 * @param solids Solid parts to add to
 */
void add_piramid(hera::Solid_parts& solids);

/**
 * @brief Add a colored cube
 * @param solids Solid parts to add to
 */
void add_cube(hera::Solid_parts& solids);

} // namespace



namespace poc
{

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
  hera::Image img;
  img.load("resources/stained.png");
  const auto tex = hera::engine.renderer.create_texture(
    img, hera::Texture::Min::Linear_mipmap_nearest, hera::Texture::Mag::Linear);
  const hera::Blend blend{.src = hera::Blend::Src_alpha, .dst = hera::Blend::One_minus_src_alpha};

  _glassy.add_part(tex, blend, {.origin = {.z = -5}});
  _glassy.add_face(
    {.z = 1},
    {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},
    {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 0}},
    {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 0}});
  _glassy.add_face(
    {.z = -1},
    {.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 1}},
    {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},
    {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}},
    {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 1}});
  _glassy.add_face(
    {.y = 1},
    {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}},
    {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 1}},
    {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 1}},
    {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}});
  _glassy.add_face(
    {.y = -1},
    {.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 0}},
    {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 0}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}});
  _glassy.add_face(
    {.x = 1},
    {.pos = {.x = 1, .y = -1, .z = -1}, .tex = {.x = 1, .y = 1}},
    {.pos = {.x = 1, .y = 1, .z = -1}, .tex = {.x = 1, .y = 0}},
    {.pos = {.x = 1, .y = 1, .z = 1}, .tex = {.x = 0, .y = 0}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .tex = {.x = 0, .y = 1}});
  _glassy.add_face(
    {.x = -1},
    {.pos = {.x = -1, .y = -1, .z = -1}, .tex = {.x = 0, .y = 1}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .tex = {.x = 1, .y = 1}},
    {.pos = {.x = -1, .y = 1, .z = 1}, .tex = {.x = 1, .y = 0}},
    {.pos = {.x = -1, .y = 1, .z = -1}, .tex = {.x = 0, .y = 0}});

  add_piramid(_solids);
  add_cube(_solids);

  _light = {
    .pos = {.z = 2},
    .ambient = {.r = 0.3, .g = 0.3, .b = 0.3, .a = 1},
    .diffuse = {.r = 1, .g = 1, .b = 1, .a = 1}};

  hera::setup_light(_light, hera::Light_id::Light1);
  hera::enable_light(hera::Light_id::Light1);
}



void Scene::handle_keys(hera::Keymap& keys)
{
  using hera::Key;
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



void Scene::render()
{
  hera::engine.renderer.basic_start_scene();
  hera::engine.set_camera(_camera);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBegin(GL_QUADS);
  glColor4ub(255, 255, 255, 255);
  glVertex3d(-0.5, -0.5, -13);
  glVertex3d(-0.5, 0.5, -13);
  glVertex3d(0.5, 0.5, -13);
  glVertex3d(0.5, -0.5, -13);
  glEnd();

  _glassy.sort_by_depth(_camera.cs().x_axis);
  hera::engine.renderer.render_parts(_solids, _glassy);
}

} // namespace poc



namespace
{

void add_piramid(hera::Solid_parts& solids)
{
  solids.add_part({}, {.origin = {.x = -1.5, .y = 0, .z = -9}});
  solids.add_face(
    {},
    {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}});
  solids.add_face(
    {},
    {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}},
    {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}});
  solids.add_face(
    {},
    {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}});
  solids.add_face(
    {},
    {.pos = {.y = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}});
}



void add_cube(hera::Solid_parts& solids)
{
  solids.add_part({}, {.origin = {.x = 1.5, .y = 0, .z = -9}});
  solids.add_face(
    {.y = 1},
    {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},
    {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 0, .g = 255, .b = 0}},
    {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}},
    {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 0, .g = 255, .b = 0}});
  solids.add_face(
    {.y = -1},
    {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255, .g = 128, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128, .b = 0}},
    {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 128, .b = 0}});
  solids.add_face(
    {.z = 1},
    {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 0, .b = 0}});
  solids.add_face(
    {.z = -1},
    {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},
    {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},
    {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}},
    {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .g = 255, .b = 0}});
  solids.add_face(
    {.x = -1},
    {.pos = {.x = -1, .y = 1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}},
    {.pos = {.x = -1, .y = 1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},
    {.pos = {.x = -1, .y = -1, .z = -1}, .color = {.r = 0, .g = 0, .b = 255}},
    {.pos = {.x = -1, .y = -1, .z = 1}, .color = {.r = 0, .g = 0, .b = 255}});
  solids.add_face(
    {.x = 1},
    {.pos = {.x = 1, .y = 1, .z = -1}, .color = {.r = 255, .g = 0, .b = 255}},
    {.pos = {.x = 1, .y = 1, .z = 1}, .color = {.r = 255, .g = 0, .b = 255}},
    {.pos = {.x = 1, .y = -1, .z = 1}, .color = {.r = 255, .g = 0, .b = 255}},
    {.pos = {.x = 1, .y = -1, .z = -1}, .color = {.r = 255, .g = 0, .b = 255}});
}

} // namespace
