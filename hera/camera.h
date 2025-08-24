#ifndef __HERA_CAMERA_H__
#define __HERA_CAMERA_H__

#include <ares/frustum.h>
#include <ares/vec2.h>

namespace hera
{

struct Camera
{
  /**
   * @brief Get camera coordinate system
   * @return Coordinate system
   */
  ares::dcs3& cs();

  /**
   * @brief Get camera coordinate system
   * @return Coordinate system
   */
  const ares::dcs3& cs() const;

  /**
   * @brief Get camera position
   * @return Position
   */
  ares::dvec3& position();

  /**
   * @brief Get camera position
   * @return Position
   */
  const ares::dvec3& position() const;

  /**
   * @brief Move the camera by the provide vector
   * @param vec Vector to move by
   */
  void translate(const ares::dvec3& vec);

  /**
   * @brief Move the camera along the x axis by the provided step
   * @param step Step by which to move
   */
  void advance(double step);

  /**
   * @brief Move the camera along the y axis by the provided step
   * @param step Step by which to move
   */
  void ascend(double step);

  /**
   * @brief Move the camera along the z axis by the provided step
   * @param step Step by which to move
   */
  void strafe(double step);

  /**
   * @brief Rotate the camera around the y axis by the provided angle in radians
   * @param angle Angle by which to rotate
   */
  void yaw(double angle);

  /**
   * @brief Rotate the camera around the z axis by the provided angle in radians
   * @param angle Angle by which to rotate
   */
  void pitch(double angle);

  /**
   * @brief Rotate the camera around the x axis by the provided angle in radians
   * @param angle Angle by which to rotate
   */
  void roll(double angle);

  /**
   * @brief Set window center from window size
   * @param x Window width center
   * @param y Window height center
   */
  void set_window_center(int x, int y);

  /**
   * @brief Set camera perspective
   * @param fov Field of view angle in radians
   * @param aspect Aspect ratio
   * @param near_dist Near distance
   * @param far_dist Far distance
   */
  void set_perspective(double fov, double aspect, double near_dist, double far_dist);

  /**
   * @brief Rotate the camera to point at the specified 3D position
   * @param pos Position to point at
   */
  void point_at(const ares::dvec3& pos);

  // Camera frustum
  ares::Frustum frustum{.cs = ares::dcs3::make({}, {.z = -1}, {.y = 1})};
  // Window center position, used to point the camera in the right direction
  ares::ivec2 center;
};



inline ares::dcs3& Camera::cs()
{
  return frustum.cs;
}



inline const ares::dcs3& Camera::cs() const
{
  return frustum.cs;
}



inline ares::dvec3& Camera::position()
{
  return frustum.cs.origin;
}



inline const ares::dvec3& Camera::position() const
{
  return frustum.cs.origin;
}



inline void Camera::translate(const ares::dvec3& vec)
{
  frustum.cs.origin += vec;
}



inline void Camera::advance(double step)
{
  frustum.cs.origin += frustum.cs.x_axis * step;
}



inline void Camera::ascend(double step)
{
  frustum.cs.origin += frustum.cs.y_axis * step;
}



inline void Camera::strafe(double step)
{
  frustum.cs.origin += frustum.cs.z_axis * step;
}



inline void Camera::yaw(double angle)
{
  frustum.cs.rotate_by_y(angle);
}



inline void Camera::pitch(double angle)
{
  frustum.cs.rotate_by_z(angle);
}



inline void Camera::roll(double angle)
{
  frustum.cs.rotate_by_x(angle);
}



inline void Camera::set_window_center(int x, int y)
{
  center.x = x;
  center.y = y;
}



inline void Camera::set_perspective(double fov, double aspect, double near_dist, double far_dist)
{
  frustum.set_perspective(fov, aspect, near_dist, far_dist);
}



inline void Camera::point_at(const ares::dvec3& pos)
{
  frustum.cs.set_x_axis((pos - frustum.cs.origin).make_normalized());
}

} // namespace hera

#endif //__HERA_CAMERA_H__
