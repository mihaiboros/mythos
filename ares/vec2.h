#ifndef __ARES_VEC2_H__
#define __ARES_VEC2_H__

#include "concepts.h"

#include <cmath>

namespace ares
{

template <typename T>
requires Arithmetic<T>
struct Vec2;

using ivec2 = Vec2<int32_t>;
using dvec2 = Vec2<double>;

/**
 * @brief Multiplication operator
 * @tparam T Scalar type
 * @tparam U Vector type
 * @param scalar Scalar value
 * @param v Vector to multiply
 * @return Vec2 Result of operation
 */
template <typename T, typename U>
requires Arithmetic<T>
constexpr Vec2<std::common_type_t<T, U>> operator*(T scalar, const Vec2<U>& v);

template <typename T>
requires Arithmetic<T>
struct Vec2
{
  /**
   * @brief Add operator
   * @tparam U Type of other vector
   * @param v Vector to add
   * @return Vec2 Result of operation
   */
  template <typename U> constexpr Vec2<std::common_type_t<T, U>> operator+(const Vec2<U>& v) const;

  /**
   * @brief Substract operator
   * @tparam U Type of other vector
   * @param v Vector to substract
   * @return Vec2 Result of operation
   */
  template <typename U> constexpr Vec2<std::common_type_t<T, U>> operator-(const Vec2<U>& v) const;

  /**
   * @brief Cross product of the vectors
   * @tparam U Type of other vector
   * @param v Vector to use in cross product
   * @return common_type_t<T, U> Result of operation
   */
  template <typename U> constexpr std::common_type_t<T, U> operator*(const Vec2<U>& v) const;

  /**
   * @brief Dot product of the vectors
   * @tparam U Type of other vector
   * @param v Vector to use in dot product
   * @return common_type_t<T, U> Result of operation
   */
  template <typename U> constexpr std::common_type_t<T, U> dot(const Vec2<U>& v) const;

  /**
   * @brief Multiplication operator
   * @tparam U Scalar type
   * @param scalar Scalar value
   * @return Vec2 Result of operation
   */
  template <typename U>
  requires Arithmetic<U>
  constexpr Vec2<std::common_type_t<T, U>> operator*(U scalar) const;

  /**
   * @brief Division operator
   * @tparam U Scalar type
   * @param scalar Scalar value
   * @return Vec2 Result of operation
   */
  template <typename U>
  requires Arithmetic<U>
  constexpr Vec2<std::common_type_t<T, U>> operator/(U scalar) const;

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

  /**
   * @brief Get a normalized vector, length of 1
   * @tparam U Used for SFINAE
   * @param eps Minimum value below which length is considered zero and normalization can't occur
   * @return Vec2 Normalized vector
   */
  template <typename U = T>
  constexpr std::enable_if_t<std::is_floating_point_v<U>, Vec2<T>> get_normalized(
    double eps = 1e-6) const;

  // value on x axis
  T x{0};
  // value on y axis
  T y{0};
};



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr Vec2<std::common_type_t<T, U>> Vec2<T>::operator+(const Vec2<U>& v) const
{
  return {.x = x + v.x, .y = y + v.y};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr Vec2<std::common_type_t<T, U>> Vec2<T>::operator-(const Vec2<U>& v) const
{
  return {.x = x - v.x, .y = y - v.y};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::common_type_t<T, U> Vec2<T>::operator*(const Vec2<U>& v) const
{
  return x * v.y - y * v.x;
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::common_type_t<T, U> Vec2<T>::dot(const Vec2<U>& v) const
{
  return x * v.x + y * v.y;
}



template <typename T>
requires Arithmetic<T>
template <typename U>
requires Arithmetic<U>
constexpr Vec2<std::common_type_t<T, U>> Vec2<T>::operator*(U scalar) const
{
  return {.x = x * scalar, .y = y * scalar};
}



template <typename T>
requires Arithmetic<T>
template <typename U>
requires Arithmetic<U>
constexpr Vec2<std::common_type_t<T, U>> Vec2<T>::operator/(U scalar) const
{
  return {.x = x / scalar, .y = y / scalar};
}



template <typename T>
requires Arithmetic<T>
constexpr bool Vec2<T>::is_zero(T eps) const
{
  if constexpr (std::is_floating_point_v<T>)
  {
    return (FP_ZERO == std::fpclassify(x) || std::abs(x) < eps)
        && (FP_ZERO == std::fpclassify(y) || std::abs(y) < eps);
  }
  else
  {
    return 0 == x && 0 == y;
  }
}



template <typename T>
requires Arithmetic<T>
constexpr double Vec2<T>::length() const
{
  return std::sqrt(x * x + y * y);
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::enable_if_t<std::is_floating_point_v<U>> Vec2<T>::normalize(double eps)
{
  if (double len = length(); FP_NORMAL == std::fpclassify(len) && len >= eps)
  {
    x /= len;
    y /= len;
  }
}



template <typename T>
requires Arithmetic<T>
template <typename U>
constexpr std::enable_if_t<std::is_floating_point_v<U>, Vec2<T>> Vec2<T>::get_normalized(
  double eps) const
{
  Vec2<T> result{*this};
  result.normalize(eps);
  return result;
}

} // namespace ares

#endif //__ARES_VEC2_H__
