#ifndef __ARES_BBOX3_H__
#define __ARES_BBOX3_H__

#include "vec3.h"

#include <initializer_list>
#include <limits>
#include <span>

namespace ares
{

struct Bbox3
{
  /**
   * @brief Make a bounding box from points
   * @param points Points to use
   * @return Bounding box
   */
  static constexpr Bbox3 make_from(std::initializer_list<const dvec3> points);

  /**
   * @brief Make a bounding box from points
   * @param points Points to use
   * @return Bounding box
   */
  static constexpr Bbox3 make_from(std::span<const dvec3> points);

  /**
   * @brief Extend bounding box with the provided point
   * @param pt Point to use
   */
  constexpr void extend(const dvec3& pt);

  /**
   * @brief Extend bounding box with the provided points
   * @param points Points to use
   */
  constexpr void extend(std::span<const dvec3> points);

  /**
   * @brief Compute the bounding box center
   * @return Center
   */
  constexpr dvec3 center() const;

  /**
   * @brief Compute the min and max corners along the provided vector direction
   * @param dir Direction to use
   * @return Min and max corners along direction
   */
  constexpr std::pair<dvec3, dvec3> corners(const dvec3& dir) const;

  /**
   * @brief Compute the min corner along the provided vector direction
   * @param dir Direction to use
   * @return Min corner along direction
   */
  constexpr dvec3 min_corner(const dvec3& dir) const;

  /**
   * @brief Compute the max corner along the provided vector direction
   * @param dir Direction to use
   * @return Max corner along direction
   */
  constexpr dvec3 max_corner(const dvec3& dir) const;

  /**
   * @brief Check if this bounding box contains the provided point
   * @param pt Point to use
   * @return Result of check
   */
  constexpr bool contains(const dvec3& pt) const;

  /**
   * @brief Check if this bounding box intersects the provided bounding box
   * @param bbox Bounding box to use
   * @return Result of check
   */
  constexpr bool intersects(const Bbox3& bbox) const;

  /**
   * @brief Compute the closest point on/in the bounding box to the provided point
   * @param pt Point to use
   * @return Closest point
   */
  constexpr dvec3 closest(const dvec3& pt) const;

  /**
   * @brief Compute the farthest point on the bounding box to the provided point
   * @param pt Point to use
   * @return Farthest point
   */
  constexpr dvec3 farthest(const dvec3& pt) const;

  // min corner of the bounding box
  dvec3 min{
    .x = std::numeric_limits<double>::max(),
    .y = std::numeric_limits<double>::max(),
    .z = std::numeric_limits<double>::max()};

  // max corner of the bounding box
  dvec3 max{
    .x = std::numeric_limits<double>::lowest(),
    .y = std::numeric_limits<double>::lowest(),
    .z = std::numeric_limits<double>::lowest()};
};



inline constexpr Bbox3 Bbox3::make_from(std::initializer_list<const dvec3> points)
{
  Bbox3 bbox;
  bbox.extend(points);
  return bbox;
}



inline constexpr Bbox3 Bbox3::make_from(std::span<const dvec3> points)
{
  Bbox3 bbox;
  bbox.extend(points);
  return bbox;
}



inline constexpr void Bbox3::extend(const dvec3& pt)
{
  min.x = std::min(min.x, pt.x);
  min.y = std::min(min.y, pt.y);
  min.z = std::min(min.z, pt.z);
  max.x = std::max(max.x, pt.x);
  max.y = std::max(max.y, pt.y);
  max.z = std::max(max.z, pt.z);
}



inline constexpr void Bbox3::extend(std::span<const dvec3> points)
{
  for (const auto& pt : points)
  {
    extend(pt);
  }
}



inline constexpr dvec3 Bbox3::center() const
{
  return (min + max) / 2;
}



inline constexpr std::pair<dvec3, dvec3> Bbox3::corners(const dvec3& dir) const
{
  const auto cx = dir.x < 0 ? std::pair{max.x, min.x} : std::pair{min.x, max.x};
  const auto cy = dir.y < 0 ? std::pair{max.y, min.y} : std::pair{min.y, max.y};
  const auto cz = dir.z < 0 ? std::pair{max.z, min.z} : std::pair{min.z, max.z};
  return {
    {.x = cx.first, .y = cy.first, .z = cz.first},
    {.x = cx.second, .y = cy.second, .z = cz.second}};
}



inline constexpr dvec3 Bbox3::min_corner(const dvec3& dir) const
{
  const auto cx = dir.x < 0 ? max.x : min.x;
  const auto cy = dir.y < 0 ? max.y : min.y;
  const auto cz = dir.z < 0 ? max.z : min.z;
  return {.x = cx, .y = cy, .z = cz};
}



inline constexpr dvec3 Bbox3::max_corner(const dvec3& dir) const
{
  const auto cx = dir.x < 0 ? min.x : max.x;
  const auto cy = dir.y < 0 ? min.y : max.y;
  const auto cz = dir.z < 0 ? min.z : max.z;
  return {.x = cx, .y = cy, .z = cz};
}



inline constexpr bool Bbox3::contains(const dvec3& pt) const
{
  return pt.x >= min.x && pt.y >= min.y && pt.z >= min.z && pt.x <= max.x && pt.y <= max.y
      && pt.z <= max.z;
}



inline constexpr bool Bbox3::intersects(const Bbox3& bbox) const
{
  return bbox.min.x <= max.x && bbox.max.x >= min.x && bbox.min.y <= max.y && bbox.max.y >= min.y
      && bbox.min.z <= max.z && bbox.max.z >= min.z;
}



inline constexpr dvec3 Bbox3::closest(const dvec3& pt) const
{
  const double x = pt.x < min.x ? min.x : pt.x > max.x ? max.x : pt.x;
  const double y = pt.y < min.y ? min.y : pt.y > max.y ? max.y : pt.y;
  const double z = pt.z < min.z ? min.z : pt.z > max.z ? max.z : pt.z;
  return {.x = x, .y = y, .z = z};
}



inline constexpr dvec3 Bbox3::farthest(const dvec3& pt) const
{
  const double x = pt.x < min.x                ? max.x
                 : pt.x > max.x                ? min.x
                 : pt.x - min.x > max.x - pt.x ? min.x
                                               : max.x;
  const double y = pt.y < min.y                ? max.y
                 : pt.y > max.y                ? min.y
                 : pt.y - min.y > max.y - pt.y ? min.y
                                               : max.y;
  const double z = pt.z < min.z                ? max.z
                 : pt.z > max.z                ? min.z
                 : pt.z - min.z > max.z - pt.z ? min.z
                                               : max.z;
  return {.x = x, .y = y, .z = z};
}

} // namespace ares

#endif //__ARES_BBOX3_H__
