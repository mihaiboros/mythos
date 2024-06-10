#include "scene.h"

#include <hera/image.h>
#include <hera/sysgl.h>

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
  mquads = {.cs = {.o = {.z = -5}},
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

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &mtex_id);
  glBindTexture(GL_TEXTURE_2D, mtex_id);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}



void Scene::draw()
{
  static double xr = 0;
  static double yr = 0;
  static double zr = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslated(mquads.cs.o.x, mquads.cs.o.y, mquads.cs.o.z);

  glRotated(xr, 1, 0, 0);
  glRotated(yr, 0, 1, 0);
  glRotated(zr, 0, 0, 1);

  glBindTexture(GL_TEXTURE_2D, mtex_id);

  glBegin(GL_QUADS);
  for (const auto& v : mquads.vertices)
  {
    glTexCoord2d(v.tex.x, v.tex.y);
    glVertex3d(v.pos.x, v.pos.y, v.pos.z);
  }
  glEnd();

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
  return {.cs = {.o = {.x = 1.5, .z = -7}},
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

  glLoadIdentity();
  glTranslated(tris.cs.o.x, tris.cs.o.y, tris.cs.o.z);
  glRotated(tr, 0, 1, 0);

  glBegin(GL_TRIANGLES);
  for (const auto& v : tris.vertices)
  {
    glColor3ub(v.color.r, v.color.g, v.color.b);
    glVertex3d(v.pos.x, v.pos.y, v.pos.z);
  }
  glEnd();

  glLoadIdentity();
  glTranslated(quads.cs.o.x, quads.cs.o.y, quads.cs.o.z);
  glRotated(qr, 1, 1, 1);

  glBegin(GL_QUADS);
  for (const auto& v : quads.vertices)
  {
    glColor3ub(v.color.r, v.color.g, v.color.b);
    glVertex3d(v.pos.x, v.pos.y, v.pos.z);
  }
  glEnd();

  tr += 0.2;
  qr -= 0.15;
}

} // namespace
