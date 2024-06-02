#ifndef __ARES_VEC3_H__
#define __ARES_VEC3_H__

#include "concepts.h"

#include <cmath>

namespace ares
{

template <typename T>
requires Arithmetic<T>
struct Vec3;

using ivec3 = Vec3<int32_t>;
using dvec3 = Vec3<double>;

template <typename T>
requires Arithmetic<T>
struct Vec3
{
  /**
   * @brief Add operator
   * @tparam U Type of other vector
   * @param v Vector to add
   * @return Vec3 Result of operation
   */
  template <typename U> constexpr Vec3<std::common_type_t<T, U>> operator+(const Vec3<U>& v) const;

  /**
   * @brief Substract operator
   * @tparam U Type of other vector
   * @param v Vector to substract
   * @return Vec3 Result of operation
   */
  template <typename U> constexpr Vec3<std::common_type_t<T, U>> operator-(const Vec3<U>& v) const;

  /**
   * @brief Cros product of the vectors
   * @tparam U Type of other vector
   * @param v Vector to use in cross product
   * @return Vec3 Result of operation
   */
  template <typename U> constexpr Vec3<std::common_type_t<T, U>> operator*(const Vec3<U>& v) const;

  /**
   * @brief Dot product of the vectors
   * @tparam U Type of other vector
   * @param v Vector to use in dot product
   * @return common_type_t<T, U> Result of operation
   */
  template <typename U> constexpr std::common_type_t<T, U> dot(const Vec3<U>& v) const;

  /**
   * @brief Check if the vector is zero
   * @param eps Minimum value below which it is considered zero
   * @return bool Result of check
   */
  constexpr bool is_zero(T eps = static_cast<T>(1e-6)) const;

  /**
   * @brief Compute the length of the vector
   * @return double Length
   */
  constexpr double length() const;

  /**
   * @brief Normalize the vector, length becoms 1
   * @tparam U Used for SFINAE
   * @param eps Minimum value below which length is considered zero and normalization can't occur
   */
  template <typename U = T>
  constexpr std::enable_if_t<std::is_floating_point_v<U>> normalize(double eps = 1e-6);

  T x{0};
  T y{0};
  T z{0};
};



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator+(const Vec3<U>& v) const
{
  return {.x = x + v.x, .y = y + v.y, .z = z + v.z};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator-(const Vec3<U>& v) const
{
  return {.x = x - v.x, .y = y - v.y, .z = z - v.z};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator*(const Vec3<U>& v) const
{
  return {.x = y * v.z - z * v.y, .y = z * v.x - x * v.z, .z = x * v.y - y * v.x};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::common_type_t<T, U> Vec3<T>::dot(const Vec3<U>& v) const
{
  return x * v.x + y * v.y + z * v.z;
}



template <typename T>
requires Arithmetic<T>
constexpr bool Vec3<T>::is_zero(T eps) const
{
  if constexpr (std::is_floating_point_v<T>)
  {
    return (FP_ZERO == std::fpclassify(x) || std::abs(x) < eps)
        && (FP_ZERO == std::fpclassify(y) || std::abs(y) < eps)
        && (FP_ZERO == std::fpclassify(z) || std::abs(z) < eps);
  }
  else
  {
    return 0 == x && 0 == y && 0 == z;
  }
}



template <typename T>
requires Arithmetic<T>
constexpr double Vec3<T>::length() const
{
  return std::sqrt(x * x + y * y + z * z);
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::enable_if_t<std::is_floating_point_v<U>> Vec3<T>::normalize(double eps)
{
  if (double len = length(); FP_NORMAL == std::fpclassify(len) && len >= eps)
  {
    x /= len;
    y /= len;
    z /= len;
  }
}

} // namespace ares

#endif //__ARES_VEC3_H__
