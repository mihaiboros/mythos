#ifndef __ARES_FRUSTUM_H__
#define __ARES_FRUSTUM_H__

#include "cs3.h"
#include "plane.h"

#include <array>
#include <cmath>

namespace ares
{

struct Frustum
{
  /**
   * @brief Make frustum from parameters
   * @param cs Frustum cs
   * @param fov Field of view angle in radians
   * @param ratio Aspect ratio
   * @param near Near distance
   * @param far Far distance
   */
  static Frustum make(const dcs3& cs, double fov, double ratio, double near, double far);

  /**
   * @brief Compute field of view half angle tangent
   * @param fov Field of view angle in radians
   * @return double Computed value
   */
  static double from_fov(double fov);

  /**
   * @brief Set frustum perspective
   * @param fov Field of view angle in radians
   * @param ratio Aspect ratio
   * @param near Near distance
   * @param far Far distance
   */
  void set_perspective(double fov, double ratio, double near, double far);

  /**
   * @brief Check that point is contained
   * @param point Point to check
   * @return bool Result of check
   */
  constexpr bool contains(const dvec3& point) const;

  /**
   * @brief Compute frustum planes
   * @return std::array<plane, 6> Frustum planes in order: near, far, bottom, top, left, right
   */
  constexpr std::array<Plane, 6> compute_planes() const;

  // Coordinate system
  dcs3 cs;
  // Field of view half angle tangent
  double fov_htan{0};
  // Aspect ratio
  double ratio{0};
  // Near distance
  double near{0};
  // Far distance
  double far{0};
};



inline Frustum Frustum::make(const dcs3& cs, double fov, double ratio, double near, double far)
{
  return {.cs = cs, .fov_htan = from_fov(fov), .ratio = ratio, .near = near, .far = far};
}



inline double Frustum::from_fov(double fov)
{
  return std::tan(fov * 0.5);
}



inline void Frustum::set_perspective(double fov, double ratio, double near, double far)
{
  fov_htan = from_fov(fov);
  this->ratio = ratio;
  this->near = near;
  this->far = far;
}



inline constexpr bool Frustum::contains(const dvec3& point) const
{
  bool result = false;

  const dvec3 v = point - cs.origin;
  const double x = v.dot(cs.x_axis);

  if (near <= x && x <= far)
  {
    const double y = v.dot(cs.y_axis);
    const double half_hy = x * fov_htan;

    if (-half_hy <= y && y <= half_hy)
    {
      const double z = v.dot(cs.z_axis);
      const double half_wy = half_hy * ratio;

      result = -half_wy <= z && z <= half_wy;
    }
  }

  return result;
}



inline constexpr std::array<Plane, 6> Frustum::compute_planes() const
{
  const dvec3 near_center = cs.origin + cs.x_axis * near;
  const double half_hnear = fov_htan * near;
  const double half_wnear = half_hnear * ratio;
  const dvec3 front = near_center - cs.origin;
  const dvec3 up = cs.y_axis * half_hnear;
  const dvec3 right = cs.z_axis * half_wnear;

  return {Plane{near_center, cs.x_axis},           // near plane
    {cs.origin + cs.x_axis * far, cs.x_axis * -1}, // far plane
    {cs.origin, cs.z_axis * (front - up)},         // bottom plane
    {cs.origin, (front + up) * cs.z_axis},         // top plane
    {cs.origin, (front - right) * cs.y_axis},      // left plane
    {cs.origin, cs.y_axis * (front + right)}};     // right plane
}

} // namespace ares

#endif //__ARES_FRUSTUM_H__
