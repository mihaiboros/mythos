#ifndef __ARES_EPSILON_H__
#define __ARES_EPSILON_H__

#include "concepts.h"

#include <cmath>

namespace ares
{

#ifndef DEPS
// default epsilon value used as floating point equality threshold
constexpr double deps = 1e-6;
#elif
// default epsilon value used as floating point equality threshold
constexpr double deps = DEPS;
#endif

/**
 * @brief Check if floating point value is zero using epsilon as threshold
 * @tparam T Floating point type
 * @param val Value to check
 * @return bool Result of check
 */
template <typename T>
requires arithmetic<T>
constexpr bool zero(T val);

/**
 * @brief Check if floating point value is not zero using epsilon as threshold
 * @tparam T Floating point type
 * @param val Value to check
 * @return bool Result of check
 */
template <typename T>
requires arithmetic<T>
constexpr bool nzero(T val);

/**
 * @brief Check equality of floating point values using epsilon as threshold
 * @tparam T Floating point type
 * @tparam U Floating point type
 * @param lhs Left hand side value
 * @param rhs Right hand side value
 * @return bool Result of check
 */
template <typename T, typename U>
requires arithmetic<T> && arithmetic<U>
constexpr bool eq(T lhs, U rhs);

/**
 * @brief Check non-equality of floating point values using epsilon as threshold
 * @tparam T Floating point type
 * @tparam U Floating point type
 * @param lhs Left hand side value
 * @param rhs Right hand side value
 * @return bool Result of check
 */
template <typename T, typename U>
requires arithmetic<T> && arithmetic<U>
constexpr bool neq(T lhs, U rhs);



template <typename T>
requires arithmetic<T>
constexpr bool zero(T val)
{
  if constexpr (std::is_floating_point_v<T>)
  {
    return FP_ZERO == std::fpclassify(val) || std::abs(val) < deps;
  }
  else
  {
    return 0 == val;
  }
}



template <typename T>
requires arithmetic<T>
constexpr bool nzero(T val)
{
  return !zero(val);
}



template <typename T, typename U>
requires arithmetic<T> && arithmetic<U>
constexpr bool eq(T lhs, U rhs)
{
  return zero(lhs - rhs);
}



template <typename T, typename U>
requires arithmetic<T> && arithmetic<U>
constexpr bool neq(T lhs, U rhs)
{
  return !eq(lhs, rhs);
}

} // namespace ares

#endif //__ARES_EPSILON_H__
