#ifndef __ARES_CCS3_H__
#define __ARES_CCS3_H__

#include "concepts.h"
#include "vec3.h"

namespace ares
{

template <typename T>
requires Floating_point<T>
struct Ccs3;

using dccs3 = Ccs3<double>;

/**
 * @brief Right handed cartesian coordinate system
 * @tparam T Arythmetic type to use
 */
template <typename T>
requires Floating_point<T>
struct Ccs3
{
  /**
   * @brief Compute x axis
   */
  constexpr void compute_x();

  /**
   * @brief Compute y axis
   */
  constexpr void compute_y();

  /**
   * @brief Compute z axis
   */
  constexpr void compute_z();

  /**
   * @brief Normalize axes
   */
  constexpr void normalize();

  /**
   * @brief Rotate around x axis
   * @param rad Angle in radians
   */
  void rotate_by_x(double rad);

  /**
   * @brief Rotate around y axis
   * @param rad Angle in radians
   */
  void rotate_by_y(double rad);

  /**
   * @brief Rotate around z axis
   * @param rad Angle in radians
   */
  void rotate_by_z(double rad);

  Vec3<T> o;
  Vec3<T> x{.x = 1};
  Vec3<T> y{.y = 1};
  Vec3<T> z{.z = 1};
};



template <typename T>
requires Floating_point<T>
constexpr void Ccs3<T>::compute_x()
{
  x = y * z;
}



template <typename T>
requires Floating_point<T>
constexpr void Ccs3<T>::compute_y()
{
  y = z * x;
}



template <typename T>
requires Floating_point<T>
constexpr void Ccs3<T>::compute_z()
{
  z = x * y;
}



template <typename T>
requires Floating_point<T>
constexpr void Ccs3<T>::normalize()
{
  x.normalize();
  y.normalize();
  z.normalize();
}



template <typename T>
requires Floating_point<T>
void Ccs3<T>::rotate_by_x(double rad)
{
  y.rotate(x, rad);
  compute_z();
}



template <typename T>
requires Floating_point<T>
void Ccs3<T>::rotate_by_y(double rad)
{
  z.rotate(y, rad);
  compute_x();
}



template <typename T>
requires Floating_point<T>
void Ccs3<T>::rotate_by_z(double rad)
{
  x.rotate(z, rad);
  compute_y();
}

} // namespace ares

#endif //__ARES_CCS3_H__
