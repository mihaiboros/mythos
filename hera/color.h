#ifndef __HERA_COLOR_H__
#define __HERA_COLOR_H__

#include <array>
#include <cstdint>

namespace hera
{

template <typename T> struct Color;

using ubColor = Color<uint8_t>;
using fColor = Color<float>;

template <typename T> struct Color
{
  /**
   * @brief Get color as an array
   * @return std::array<T, 4> Color array
   */
  std::array<T, 4> rgba() const;

  // red
  T r{0};
  // green
  T g{0};
  // blue
  T b{0};
  // alpha
  T a{0};
};



template <typename T> std::array<T, 4> Color<T>::rgba() const
{
  return {r, g, b, a};
}

} // namespace hera

#endif //__HERA_COLOR_H__
