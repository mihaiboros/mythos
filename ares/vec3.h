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

/**
 * @brief Multiplication operator
 * @tparam T Scalar type
 * @tparam U Vector type
 * @param scalar Scalar value
 * @param v Vector to multiply
 * @return Vec3 Result of operation
 */
template <typename T, typename U>
requires Arithmetic<T>
constexpr Vec3<std::common_type_t<T, U>> operator*(T scalar, const Vec3<U>& v);

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
   * @brief Cross product of the vectors
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
   * @brief Multiplication operator
   * @tparam U Scalar type
   * @param scalar Scalar value
   * @return Vec3 Result of operation
   */
  template <typename U>
  requires Arithmetic<U>
  constexpr Vec3<std::common_type_t<T, U>> operator*(U scalar) const;

  /**
   * @brief Division operator
   * @tparam U Scalar type
   * @param scalar Scalar value
   * @return Vec3 Result of operation
   */
  template <typename U>
  requires Arithmetic<U>
  constexpr Vec3<std::common_type_t<T, U>> operator/(U scalar) const;

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
   * @brief Normalize the vector, length becomes 1
   * @tparam U Used for SFINAE
   * @param eps Minimum value below which length is considered zero and normalization can't occur
   */
  template <typename U = T>
  constexpr std::enable_if_t<std::is_floating_point_v<U>> normalize(T eps = 1e-6);

  /**
   * @brief Get a normalized vector, length of 1
   * @tparam U Used for SFINAE
   * @param eps Minimum value below which length is considered zero and normalization can't occur
   * @return Vec3 Normalized vector
   */
  template <typename U = T>
  constexpr std::enable_if_t<std::is_floating_point_v<U>, Vec3<T>> get_normalized(
    T eps = 1e-6) const;

  /**
   * @brief Rotate the vector around an axis by the provide angle in radians
   * @tparam U U Type of other vector
   * @tparam V Used for SFINAE
   * @param norm_ax Normalized axis to rotate around. Must be normalized!
   * @param rad Angle to rotate by in radians
   * @return constexpr std::enable_if_t<std::is_floating_point_v<V>>
   */
  template <typename U, typename V = T>
  constexpr std::enable_if_t<std::is_floating_point_v<V>> rotate(const Vec3<U>& norm_ax, T rad);

  // value on x axis
  T x{0};
  // value on y axis
  T y{0};
  // value on z axis
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
template <typename U>
requires Arithmetic<U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator*(U scalar) const
{
  return {.x = x * scalar, .y = y * scalar, .z = z * scalar};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
requires Arithmetic<U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator/(U scalar) const
{
  return {.x = x / scalar, .y = y / scalar, .z = z / scalar};
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
constexpr std::enable_if_t<std::is_floating_point_v<U>> Vec3<T>::normalize(T eps)
{
  if (T len = length(); FP_NORMAL == std::fpclassify(len) && len >= eps)
  {
    x /= len;
    y /= len;
    z /= len;
  }
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::enable_if_t<std::is_floating_point_v<U>, Vec3<T>> Vec3<T>::get_normalized(
  T eps) const
{
  Vec3<T> result{*this};
  result.normalize(eps);
  return result;
}



template <typename T>
requires Arithmetic<T>
template <typename U, typename V>
constexpr std::enable_if_t<std::is_floating_point_v<V>> Vec3<T>::rotate(
  const Vec3<U>& norm_ax, T rad)
{
  const T cost = std::cos(rad);
  const T sint = std::sin(rad);

  const auto& v = *this;
  const auto rot = cost * v + sint * (norm_ax * v) + (1 - cost) * norm_ax.dot(v) * norm_ax;

  x = rot.x;
  y = rot.y;
  z = rot.z;
}



template <typename T, typename U>
requires Arithmetic<T>
constexpr Vec3<std::common_type_t<T, U>> operator*(T scalar, const Vec3<U>& v)
{
  return {.x = scalar * v.x, .y = scalar * v.y, .z = scalar * v.z};
}

} // namespace ares

#endif //__ARES_VEC3_H__
