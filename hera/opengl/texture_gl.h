#ifndef __HERA_TEXTURE_GL_H__
#define __HERA_TEXTURE_GL_H__

#include "../image.h"
#include "sysgl.h"

#include <cstdint>

namespace hera
{

enum class Filter
{
  Nearest = GL_NEAREST,
  Linear = GL_LINEAR,
  Linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST
};

/**
 * @brief Make texture from image
 * @param img Image to use
 * @param min Min filter
 * @param mag Mag filter
 * @return uint32_t Texture id
 */
uint32_t make_texture(const Image& img, Filter min, Filter mag);

/**
 * @brief Bind texture for use
 * @param tex Texture to bind
 */
void bind_texture(uint32_t tex);

} // namespace hera



namespace hera
{

inline uint32_t make_texture(const Image& img, Filter min, Filter mag)
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



inline void bind_texture(uint32_t tex)
{
  glBindTexture(GL_TEXTURE_2D, tex);
}

} // namespace hera

#endif //__HERA_TEXTURE_GL_H__
