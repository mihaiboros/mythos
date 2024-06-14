#ifndef __HERA_MODEL_GL_H__
#define __HERA_MODEL_GL_H__

#include "../model.h"
#include "sysgl.h"

namespace hera
{

/**
 * @brief Render model with color
 * @param model Model to render
 * @param xr Rotation around x axis
 * @param yr Rotation around y axis
 * @param zr Rotation around z axis
 */
void render_colored(const Model& model, double xr, double yr, double zr);

/**
 * @brief Render model with texture
 * @param model Model to render
 * @param xr Rotation around x axis
 * @param yr Rotation around y axis
 * @param zr Rotation around z axis
 */
void render_textured(const Model& model, double xr, double yr, double zr);

} // namespace hera



namespace hera
{

inline void render_colored(const Model& model, double xr, double yr, double zr)
{
  glLoadIdentity();
  glTranslated(model.cs.o.x, model.cs.o.y, model.cs.o.z);

  glRotated(xr, 1, 0, 0);
  glRotated(yr, 0, 1, 0);
  glRotated(zr, 0, 0, 1);

  glBegin(model.has_quads ? GL_QUADS : GL_TRIANGLES);
  for (const auto& v : model.vertices)
  {
    glColor3ub(v.color.r, v.color.g, v.color.b);
    glVertex3d(v.pos.x, v.pos.y, v.pos.z);
  }
  glEnd();
}



inline void render_textured(const Model& model, double xr, double yr, double zr)
{
  glLoadIdentity();
  glTranslated(model.cs.o.x, model.cs.o.y, model.cs.o.z);

  glRotated(xr, 1, 0, 0);
  glRotated(yr, 0, 1, 0);
  glRotated(zr, 0, 0, 1);

  glBegin(model.has_quads ? GL_QUADS : GL_TRIANGLES);
  for (const auto& v : model.vertices)
  {
    glTexCoord2d(v.tex.x, v.tex.y);
    glVertex3d(v.pos.x, v.pos.y, v.pos.z);
  }
  glEnd();
}

} // namespace hera

#endif //__HERA_MODEL_GL_H__
