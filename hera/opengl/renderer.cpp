#include "../renderer.h"

#include "heragl.h"

namespace hera
{

void Renderer::basic_scene_setup() const
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 0);
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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



const ares::dVec3 Renderer::un_project(double winx, double winy, double winz) const
{
  ares::dVec3 pos;
  glGetDoublev(GL_MODELVIEW_MATRIX, _matrix1.data);
  glGetDoublev(GL_PROJECTION_MATRIX, _matrix2.data);
  const int revy = _viewport[Vp::height] - winy - 1;
  gluUnProject(winx, revy, winz, _matrix1.data, _matrix2.data, _viewport, &pos.x, &pos.y, &pos.z);
  return pos;
}



void Renderer::look_at(
  const ares::dVec3& eye, const ares::dVec3& center, const ares::dVec3& up) const
{
  gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

} // namespace hera
