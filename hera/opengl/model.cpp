#include "../model.h"

#include "heragl.h"

#include <span>

namespace hera
{

void Model::render_colored(double xr, double yr, double zr) const
{
  glLoadIdentity();
  glTranslated(cs.origin.x, cs.origin.y, cs.origin.z);

  glRotated(xr, 1, 0, 0);
  glRotated(yr, 0, 1, 0);
  glRotated(zr, 0, 0, 1);

  const int step = has_quads ? 4 : 3;
  int pos = 0;

  glBegin(has_quads ? GL_QUADS : GL_TRIANGLES);
  for (const auto& f : faces)
  {
    glNormal3d(f.normal.x, f.normal.y, f.normal.z);
    for (const auto& v : std::span{vertices.begin() + pos, vertices.begin() + pos + step})
    {
      glColor3ub(v.color.r, v.color.g, v.color.b);
      glVertex3d(v.pos.x, v.pos.y, v.pos.z);
    }
    pos += step;
  }
  glEnd();
}



void Model::render_textured(double xr, double yr, double zr) const
{
  glLoadIdentity();
  glTranslated(cs.origin.x, cs.origin.y, cs.origin.z);

  glRotated(xr, 1, 0, 0);
  glRotated(yr, 0, 1, 0);
  glRotated(zr, 0, 0, 1);

  const int step = has_quads ? 4 : 3;
  int pos = 0;

  glBegin(has_quads ? GL_QUADS : GL_TRIANGLES);
  for (const auto& f : faces)
  {
    glNormal3d(f.normal.x, f.normal.y, f.normal.z);
    for (const auto& v : std::span{vertices.begin() + pos, vertices.begin() + pos + step})
    {
      glTexCoord2d(v.tex.x, v.tex.y);
      glVertex3d(v.pos.x, v.pos.y, v.pos.z);
    }
    pos += step;
  }
  glEnd();
}



void Model::bind_texture() const
{
  glBindTexture(GL_TEXTURE_2D, tex);
}

} // namespace hera
