#ifndef __ARES_CONCEPTS_H__
#define __ARES_CONCEPTS_H__

#include <concepts>

namespace ares
{

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept Floating_point = std::is_floating_point_v<T>;

} // namespace ares

#endif //__ARES_CONCEPTS_H__
