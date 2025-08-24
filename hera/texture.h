#ifndef __HERA_TEXTURE_H__
#define __HERA_TEXTURE_H__

#include <cstdint>

namespace hera
{

struct Texture
{
  // magnification filter
  enum class Mag
  {
    Nearest = 0,
    Linear
  };

  // minimization filter
  enum class Min
  {
    Nearest = Mag::Nearest,
    Linear = Mag::Linear,
    Nearest_mipmap_nearest,
    Linear_mipmap_nearest,
    Nearest_mipmap_linear,
    Linear_mipmap_linear
  };

  // texture id
  int32_t id{0};
};

} // namespace hera

#endif //__HERA_TEXTURE_H__
