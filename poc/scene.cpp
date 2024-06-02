#include "scene.h"

#include "sysgl.h"

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



void Scene::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glBegin(GL_TRIANGLES);
  glVertex3d(-1.5, 1, -6);
  glVertex3d(-2.5, -1, -6);
  glVertex3d(-0.5, -1, -6);
  glEnd();

  glBegin(GL_QUADS);
  glVertex3d(0.5, 1, -6);
  glVertex3d(2.5, 1, -6);
  glVertex3d(2.5, -1, -6);
  glVertex3d(0.5, -1, -6);
  glEnd();
}

} // namespace poc
