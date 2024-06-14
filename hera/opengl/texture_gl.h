#ifndef __HERA_TEXTURE_GL_H__
#define __HERA_TEXTURE_GL_H__

#include "../image.h"
#include "sysgl.h"

#include <cstdint>

namespace hera
{

/**
 * @brief Make texture from image
 * @param img Image to bind
 * @return uint32_t Texture id
 */
uint32_t make_texture(const Image& img);

/**
 * @brief Bind texture for use
 * @param tex Texture to bind
 */
void bind_texture(uint32_t tex);

} // namespace hera



namespace hera
{

inline uint32_t make_texture(const Image& img)
{
  uint32_t tex = 0;

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}



inline void bind_texture(uint32_t tex)
{
  glBindTexture(GL_TEXTURE_2D, tex);
}

} // namespace hera

#endif //__HERA_TEXTURE_GL_H__
