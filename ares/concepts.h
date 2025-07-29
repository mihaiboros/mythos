#ifndef __ARES_CONCEPTS_H__
#define __ARES_CONCEPTS_H__

#include <concepts>

namespace ares
{

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

} // namespace ares

#endif //__ARES_CONCEPTS_H__
