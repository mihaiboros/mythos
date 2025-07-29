#ifndef __HERA_ENUMS_H__
#define __HERA_ENUMS_H__

#include "heragl.h"

namespace hera
{

enum class Filter
{
  Nearest = GL_NEAREST,
  Linear = GL_LINEAR,
  Linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST
};

enum class Blend
{
  One = GL_ONE,
  Src_alpha = GL_SRC_ALPHA,
  One_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
  Dst_alpha = GL_DST_ALPHA,
  One_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA
};

} // namespace hera

#endif //__HERA_ENUMS_H__
