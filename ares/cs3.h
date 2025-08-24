#ifndef __ARES_CS3_H__
#define __ARES_CS3_H__

#include "concepts.h"
#include "vec3.h"

namespace ares
{

template <std::floating_point T>
struct Cs3;

using dcs3 = Cs3<double>;

/**
 * @brief Right handed cartesian coordinate system
 * @tparam T Arythmetic type to use
 */
template <std::floating_point T>
struct Cs3
{
  /**
   * @brief Make coordinate system from parameters, will auto compute z axis
   * @param origin Origin
   * @param x_axis X axis, must be normalized
   * @param y_axis Y axis, must be normalized
   * @return Coordinate system
   */
  static constexpr Cs3 make(const Vec3<T>& origin, const Vec3<T>& x_axis, const Vec3<T>& y_axis);

  /**
   * @brief Set the x axis, computes the other axis
   * @param x_axis X axis to set, must be normalized
   */
  constexpr void set_x_axis(const Vec3<T>& x_axis);

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
  constexpr void rotate_by_x(double rad);

  /**
   * @brief Rotate around y axis
   * @param rad Angle in radians
   */
  constexpr void rotate_by_y(double rad);

  /**
   * @brief Rotate around z axis
   * @param rad Angle in radians
   */
  constexpr void rotate_by_z(double rad);

  Vec3<T> origin;
  Vec3<T> x_axis{.x = 1}; // must be normalized
  Vec3<T> y_axis{.y = 1}; // must be normalized
  Vec3<T> z_axis{.z = 1}; // must be normalized
};



template <std::floating_point T>
constexpr Cs3<T> Cs3<T>::make(const Vec3<T>& origin, const Vec3<T>& x_axis, const Vec3<T>& y_axis)
{
  return {.origin = origin, .x_axis = x_axis, .y_axis = y_axis, .z_axis = x_axis * y_axis};
}



template <std::floating_point T>
constexpr void Cs3<T>::set_x_axis(const Vec3<T>& x_axis)
{
  if (x_axis.is_zero())
  {
    return;
  }

  this->x_axis = x_axis;
  if (x_axis.is_parallel(z_axis))
  {
    z_axis = x_axis * y_axis;
    y_axis = z_axis * x_axis;
  }
  else
  {
    y_axis = z_axis * x_axis;
    z_axis = x_axis * y_axis;
  }
}



template <std::floating_point T>
constexpr void Cs3<T>::compute_x()
{
  x_axis = y_axis * z_axis;
}



template <std::floating_point T>
constexpr void Cs3<T>::compute_y()
{
  y_axis = z_axis * x_axis;
}



template <std::floating_point T>
constexpr void Cs3<T>::compute_z()
{
  z_axis = x_axis * y_axis;
}



template <std::floating_point T>
constexpr void Cs3<T>::normalize()
{
  x_axis.normalize();
  y_axis.normalize();
  z_axis.normalize();
}



template <std::floating_point T>
constexpr void Cs3<T>::rotate_by_x(double rad)
{
  y_axis.rotate(x_axis, rad);
  compute_z();
}



template <std::floating_point T>
constexpr void Cs3<T>::rotate_by_y(double rad)
{
  z_axis.rotate(y_axis, rad);
  compute_x();
}



template <std::floating_point T>
constexpr void Cs3<T>::rotate_by_z(double rad)
{
  x_axis.rotate(z_axis, rad);
  compute_y();
}

} // namespace ares

#endif //__ARES_CS3_H__
