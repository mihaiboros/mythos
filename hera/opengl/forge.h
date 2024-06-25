#ifndef __HERA_FORGE_H__
#define __HERA_FORGE_H__

#include "../image.h"
#include "enums.h"
#include "sysgl.h"

#include <cstdint>

namespace hera::forge
{

/**
 * @brief Make texture from image
 * @param img Image to use
 * @param min Min filter
 * @param mag Mag filter
 * @return uint32_t Texture id
 */
uint32_t make_texture(const Image& img, Filter min, Filter mag);

} // namespace hera::forge

#endif //__HERA_FORGE_H__
