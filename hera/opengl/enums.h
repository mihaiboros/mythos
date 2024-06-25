#ifndef __HERA_ENUMS_H__
#define __HERA_ENUMS_H__

#include "sysgl.h"

namespace hera
{

enum class Filter
{
  Nearest = GL_NEAREST,
  Linear = GL_LINEAR,
  Linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST
};

} // namespace hera

#endif //__HERA_ENUMS_H__
