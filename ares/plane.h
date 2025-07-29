#ifndef __ARES_PLANE_H__
#define __ARES_PLANE_H__

#include "epsilon.h"
#include "vec3.h"

namespace ares
{

/**
 * @brief Geometric plane
 */
struct Plane
{
  /**
   * @brief C++ constructor
   * @param pt Point on plane
   * @param norm Plane normal, must be normalized
   */
  constexpr Plane(const dVec3& pt, const dVec3& norm);

  /**
   * @brief C++ constructor
   * @param p0 Point on plane
   * @param p1 Point on plane
   * @param p2 Point on plane
   */
  constexpr Plane(const dVec3& p0, const dVec3& p1, const dVec3& p2);

  /**
   * @brief Adjust plane for a new position and normal
   * @param pt Point to use in adjustment
   */
  constexpr void adjust(const dVec3& pt);

  /**
   * @brief Compute distance from plane to point. Negative if point is on the back side of the plane
   * @param point Point to use
   * @return Distance to point. Negative if on the back side
   */
  constexpr double distance(const dVec3& point) const;

  /**
   * @brief Check if point is on this plane
   * @param point Point to check
   * @return Result of check
   */
  constexpr bool contains(const dVec3& point) const;

  /**
   * @brief Project point on this plane
   * @param point Point to project
   * @return Projected point
   */
  constexpr dVec3 project(const dVec3& point) const;

  // Plane normal, must be normalized. Adjust plane if changed
  dVec3 normal{.y = 1};

  // Plane D coefficient
  double d{0};
};



inline constexpr Plane::Plane(const dVec3& pt, const dVec3& norm) : normal{norm}
{
  adjust(pt);
}



inline constexpr Plane::Plane(const dVec3& p0, const dVec3& p1, const dVec3& p2)
  : normal(((p1 - p0) * (p2 - p0)).make_normalized())
{
  adjust(p0);
}



inline constexpr void Plane::adjust(const dVec3& pt)
{
  d = -normal.dot(pt);
}



inline constexpr double Plane::distance(const dVec3& point) const
{
  return normal.dot(point) + d;
}



inline constexpr bool Plane::contains(const dVec3& point) const
{
  return zero(distance(point));
}



inline constexpr dVec3 Plane::project(const dVec3& point) const
{
  return point - normal * distance(point);
}

} // namespace ares

#endif //__ARES_PLANE_H__
