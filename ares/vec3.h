#ifndef __ARES_VEC3_H__
#define __ARES_VEC3_H__

#include "concepts.h"
#include "epsilon.h"

#include <array>
#include <cmath>

namespace ares
{

template <arithmetic T>
struct Vec3;

using dvec3 = Vec3<double>;
using fvec3 = Vec3<float>;
using ivec3 = Vec3<int32_t>;

/**
 * @brief Multiplication operator
 * @tparam T Scalar type
 * @tparam U Vector type
 * @param scalar Scalar value
 * @param v Vector to multiply
 * @return Result of operation
 */
template <arithmetic T, typename U>
constexpr Vec3<std::common_type_t<T, U>> operator*(T scalar, const Vec3<U>& v);

template <arithmetic T>
struct Vec3
{
  /**
   * @brief Equality operator
   * @param v Vector to compare with
   * @return bool Result of comparison
   */
  template <typename U>
  constexpr bool operator==(const Vec3<U>& v) const;

  /**
   * @brief Inequality operator
   * @param v Vector to compare with
   * @return bool Result of comparison
   */
  template <typename U>
  constexpr bool operator!=(const Vec3<U>& v) const;

  /**
   * @brief Less than operator
   * @param v Vector to compare with
   * @return bool Result of comparison
   */
  template <typename U>
  constexpr bool operator<(const Vec3<U>& v) const;

  /**
   * @brief Add operator
   * @tparam U Type of other vector
   * @param v Vector to add
   * @return Result of operation
   */
  template <typename U>
  constexpr Vec3<std::common_type_t<T, U>> operator+(const Vec3<U>& v) const;

  /**
   * @brief Addition assignment operator
   * @tparam U Type of other vector
   * @param v Vector to add
   */
  template <typename U>
  constexpr void operator+=(const Vec3<U>& v);

  /**
   * @brief Substract operator
   * @tparam U Type of other vector
   * @param v Vector to substract
   * @return Result of operation
   */
  template <typename U>
  constexpr Vec3<std::common_type_t<T, U>> operator-(const Vec3<U>& v) const;

  /**
   * @brief Subtraction assignment operator
   * @tparam U Type of other vector
   * @param v Vector to substract
   */
  template <typename U>
  constexpr void operator-=(const Vec3<U>& v);

  /**
   * @brief Cross product of the vectors
   * @tparam U Type of other vector
   * @param v Vector to use in cross product
   * @return Result of operation
   */
  template <typename U>
  constexpr Vec3<std::common_type_t<T, U>> operator*(const Vec3<U>& v) const;

  /**
   * @brief Dot product of the vectors
   * @tparam U Type of other vector
   * @param v Vector to use in dot product
   * @return common_type_t<T, U> Result of operation
   */
  template <typename U>
  constexpr std::common_type_t<T, U> dot(const Vec3<U>& v) const;

  /**
   * @brief Multiplication operator
   * @tparam U Scalar type
   * @param scalar Scalar value
   * @return Result of operation
   */
  template <arithmetic U>
  constexpr Vec3<std::common_type_t<T, U>> operator*(U scalar) const;

  /**
   * @brief Multiplication assignment operator
   * @param scalar Scalar value
   */
  template <arithmetic U>
  constexpr void operator*=(U scalar);

  /**
   * @brief Division operator
   * @tparam U Scalar type
   * @param scalar Scalar value
   * @return Result of operation
   */
  template <arithmetic U>
  constexpr Vec3<std::common_type_t<T, U>> operator/(U scalar) const;

  /**
   * @brief Division assignment operator
   * @param scalar Scalar value
   */
  template <arithmetic U>
  constexpr void operator/=(U scalar);

  /**
   * @brief Get vector as an array
   * @tparam U Array type
   * @return std::array<U, 4> Coordinates array
   */
  template <arithmetic U = T>
  std::array<U, 4> xyzw() const;

  /**
   * @brief Check if the vector is zero
   * @return bool Result of check
   */
  constexpr bool is_zero() const;

  /**
   * @brief Compute the length of the vector
   * @return double Length
   */
  constexpr double length() const;

  /**
   * @brief Normalize the vector, length becomes 1
   * @tparam U Used for SFINAE
   */
  template <typename U = T>
  constexpr std::enable_if_t<std::is_floating_point_v<U>> normalize();

  /**
   * @brief Make a normalized vector, length of 1
   * @tparam U Used for SFINAE
   * @return Normalized vector
   */
  template <typename U = T>
  constexpr std::enable_if_t<std::is_floating_point_v<U>, Vec3<T>> make_normalized() const;

  /**
   * @brief Rotate the vector around an axis by the provide angle in radians
   * @tparam U Type of other vector
   * @tparam V Used for SFINAE
   * @param norm_ax Normalized axis to rotate around. Must be normalized!
   * @param rad Angle to rotate by in radians
   * @return constexpr std::enable_if_t<std::is_floating_point_v<V>>
   */
  template <typename U, typename V = T>
  constexpr std::enable_if_t<std::is_floating_point_v<V>> rotate(const Vec3<U>& norm_ax, T rad);

  /**
   * @brief Check if vectors are parallel
   * @tparam U Type of other vector
   * @param v Vector to check
   * @return Result of check
   */
  template <typename U>
  constexpr bool is_parallel(const Vec3<U>& v) const;

  /**
   * @brief Check if vectors are parallel and have the same direction
   * @tparam U Type of other vector
   * @param v Vector to check
   * @return Result of check
   */
  template <typename U>
  constexpr bool is_codir(const Vec3<U>& v) const;

  /**
   * @brief Check if vectors are parallel and have opposite direction
   * @tparam U Type of other vector
   * @param v Vector to check
   * @return Result of check
   */
  template <typename U>
  constexpr bool is_contradir(const Vec3<U>& v) const;

  /**
   * @brief Check if this point is coplanar with the provided points
   * @tparam P0 Type of other point
   * @tparam P1 Type of other point
   * @tparam P2 Type of other point
   * @param pt0 Point on plane
   * @param pt1 Point on plane
   * @param pt2 Point on plane
   * @return Result of check
   */
  template <typename P0, typename P1, typename P2>
  constexpr bool is_coplanar(const Vec3<P0>& pt0, const Vec3<P1>& pt1, const Vec3<P2>& pt2) const;

  /**
   * @brief Compute distance between points
   * @tparam P Type of other point
   * @param pt Point to use
   * @return Distance
   */
  template <typename P>
  constexpr double distance_to(const Vec3<P>& pt) const;

  // value on x axis
  T x{0};
  // value on y axis
  T y{0};
  // value on z axis
  T z{0};
};



template <arithmetic T>
template <typename U>
constexpr bool Vec3<T>::operator==(const Vec3<U>& v) const
{
  return eq(x, v.x) && eq(y, v.y) && eq(z, v.z);
}



template <arithmetic T>
template <typename U>
constexpr bool Vec3<T>::operator!=(const Vec3<U>& v) const
{
  return !(*this == v);
}



template <arithmetic T>
template <typename U>
constexpr bool Vec3<T>::operator<(const Vec3<U>& v) const
{
  return neq(x, v.x) ? x < v.x : neq(y, v.y) ? y < v.y : z < v.z;
}



template <arithmetic T>
template <typename U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator+(const Vec3<U>& v) const
{
  return {.x = x + v.x, .y = y + v.y, .z = z + v.z};
}



template <arithmetic T>
template <typename U>
constexpr void Vec3<T>::operator+=(const Vec3<U>& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
}



template <arithmetic T>
template <typename U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator-(const Vec3<U>& v) const
{
  return {.x = x - v.x, .y = y - v.y, .z = z - v.z};
}



template <arithmetic T>
template <typename U>
constexpr void Vec3<T>::operator-=(const Vec3<U>& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
}



template <arithmetic T>
template <typename U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator*(const Vec3<U>& v) const
{
  return {.x = y * v.z - z * v.y, .y = z * v.x - x * v.z, .z = x * v.y - y * v.x};
}



template <arithmetic T>
template <typename U>
constexpr std::common_type_t<T, U> Vec3<T>::dot(const Vec3<U>& v) const
{
  return x * v.x + y * v.y + z * v.z;
}



template <arithmetic T>
template <arithmetic U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator*(U scalar) const
{
  return {.x = x * scalar, .y = y * scalar, .z = z * scalar};
}



template <arithmetic T>
template <arithmetic U>
constexpr void Vec3<T>::operator*=(U scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
}



template <arithmetic T>
template <arithmetic U>
constexpr Vec3<std::common_type_t<T, U>> Vec3<T>::operator/(U scalar) const
{
  return {.x = x / scalar, .y = y / scalar, .z = z / scalar};
}



template <arithmetic T>
template <arithmetic U>
constexpr void Vec3<T>::operator/=(U scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
}



template <arithmetic T>
template <arithmetic U>
std::array<U, 4> Vec3<T>::xyzw() const
{
  return {x, y, z, 1};
}



template <arithmetic T>
constexpr bool Vec3<T>::is_zero() const
{
  return zero(x) && zero(y) && zero(z);
}



template <arithmetic T>
constexpr double Vec3<T>::length() const
{
  return std::sqrt(x * x + y * y + z * z);
}



template <arithmetic T>
template <typename U>
constexpr std::enable_if_t<std::is_floating_point_v<U>> Vec3<T>::normalize()
{
  if (const T len = length(); !zero(len))
  {
    x /= len;
    y /= len;
    z /= len;
  }
}



template <arithmetic T>
template <typename U>
constexpr std::enable_if_t<std::is_floating_point_v<U>, Vec3<T>> Vec3<T>::make_normalized() const
{
  const T len = length();
  return zero(len) ? *this : Vec3<T>{.x = x / len, .y = y / len, .z = z / len};
}



template <arithmetic T>
template <typename U, typename V>
constexpr std::enable_if_t<std::is_floating_point_v<V>>
Vec3<T>::rotate(const Vec3<U>& norm_ax, T rad)
{
  const T cost = std::cos(rad);
  const T sint = std::sin(rad);

  const auto& v = *this;
  const auto rot = cost * v + sint * (norm_ax * v) + (1 - cost) * norm_ax.dot(v) * norm_ax;

  x = rot.x;
  y = rot.y;
  z = rot.z;
}



template <arithmetic T>
template <typename U>
constexpr bool Vec3<T>::is_parallel(const Vec3<U>& v) const
{
  const double len_prod = length() * v.length();
  return len_prod != 0 && eq(std::abs(dot(v) / len_prod), 1);
}



template <arithmetic T>
template <typename U>
constexpr bool Vec3<T>::is_codir(const Vec3<U>& v) const
{
  const double len_prod = length() * v.length();
  return len_prod != 0 && eq(dot(v) / len_prod, 1);
}



template <arithmetic T>
template <typename U>
constexpr bool Vec3<T>::is_contradir(const Vec3<U>& v) const
{
  const double len_prod = length() * v.length();
  return len_prod != 0 && eq(dot(v) / len_prod, -1);
}



template <arithmetic T>
template <typename P0, typename P1, typename P2>
constexpr bool
Vec3<T>::is_coplanar(const Vec3<P0>& pt0, const Vec3<P1>& pt1, const Vec3<P2>& pt2) const
{
  return eq((pt0 - *this).dot((pt1 - *this) * (pt2 - *this)), 0);
}



template <arithmetic T>
template <typename P>
constexpr double Vec3<T>::distance_to(const Vec3<P>& pt) const
{
  return (*this - pt).length();
}



template <arithmetic T, typename U>
constexpr Vec3<std::common_type_t<T, U>> operator*(T scalar, const Vec3<U>& v)
{
  return {.x = scalar * v.x, .y = scalar * v.y, .z = scalar * v.z};
}

} // namespace ares

#endif //__ARES_VEC3_H__
