#include "scene.h"

#include <hera/sysgl.h>

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
  tri.cs.o = {.x = -1.5, .z = -6};
  tri.vertices = {hera::Vertex{.pos = {.y = 1}, .color = {.r = 255}},
    hera::Vertex{.pos = {.x = -1, .y = -1}, .color = {.g = 255}},
    hera::Vertex{.pos = {.x = 1, .y = -1}, .color = {.b = 255}}};

  const hera::Color qc{.r = 128, .g = 128, .b = 255};
  quad.cs.o = {.x = 1.5, .z = -6};
  quad.vertices = {hera::Vertex{.pos = {.x = -1, .y = 1}, .color = qc},
    hera::Vertex{.pos = {.x = 1, .y = 1}, .color = qc},
    hera::Vertex{.pos = {.x = 1, .y = -1}, .color = qc},
    hera::Vertex{.pos = {.x = -1, .y = -1}, .color = qc}};
}



double rtri = 0;
double rqua = 0;
void Scene::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotated(rtri, 0, 1, 0);
  glBegin(GL_TRIANGLES);
  glColor3d(1, 0, 0);
  glVertex3d(-1.5, 1, -6);
  glColor3d(0, 1, 0);
  glVertex3d(-2.5, -1, -6);
  glColor3d(0, 0, 1);
  glVertex3d(-0.5, -1, -6);
  glEnd();

  glLoadIdentity();
  glRotated(rqua, 1, 0, 0);
  glColor3ub(128, 128, 255);
  glBegin(GL_QUADS);
  glVertex3d(0.5, 1, -6);
  glVertex3d(2.5, 1, -6);
  glVertex3d(2.5, -1, -6);
  glVertex3d(0.5, -1, -6);
  glEnd();

  rtri += 0.2;
  rqua -= 0.15;
}

} // namespace poc
