#include "forge.h"

namespace hera::forge
{

uint32_t texture(const Image& img, Filter min, Filter mag)
{
  uint32_t tex = 0;

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &tex);

  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(min));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(mag));
  if ((Filter::Nearest == min || Filter::Linear == min)
      && (Filter::Nearest == mag || Filter::Linear == mag))
  {
    glTexImage2D(GL_TEXTURE_2D,
      0,
      3,
      img.width,
      img.height,
      0,
      img.has_alpha ? GL_RGBA : GL_RGB,
      GL_UNSIGNED_BYTE,
      img.data());
  }
  else
  {
    gluBuild2DMipmaps(GL_TEXTURE_2D,
      3,
      img.width,
      img.height,
      img.has_alpha ? GL_RGBA : GL_RGB,
      GL_UNSIGNED_BYTE,
      img.data());
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}

} // namespace hera::forge
