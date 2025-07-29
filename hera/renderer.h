#ifndef __HERA_RENDERER_H__
#define __HERA_RENDERER_H__

#include <ares/matrix.h>
#include <ares/vec2.h>
#include <ares/vec3.h>

namespace hera
{

class Renderer
{
public:

  /**
   * @brief Basic scene setup
   */
  void basic_scene_setup() const;

  /**
   * @brief Set viewport
   * @param x Viewport position
   * @param y Viewport position
   * @param width Viewport width
   * @param height Viewport height
   */
  void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);

  /**
   * @brief Set perspective
   * @param push_mvp Push mvp matrix
   * @param fov Field of view
   * @param aspect Aspect ratio
   * @param znear Near clipping plane z distance
   * @param zfar Far clipping plane z distance
   */
  void set_perspective(bool push_mvp, double fov, double aspect, double znear, double zfar) const;

  /**
   * @brief Map window coordinates to object coordinates
   * @param winx X window coordinate to be mapped
   * @param winy Y window coordinate to be mapped
   * @param winz Z window coordinate to be mapped (ussualy is 1)
   * @return Window corrdinates in 3D space
   */
  const ares::dVec3 un_project(double winx, double winy, double winz = 1) const;

  /**
   * @brief Define a view transform setting the "camera" eye position looking at center position
   * @param eye Position of the eye
   * @param center Position of the look at point
   * @param up Camera up
   */
  void look_at(const ares::dVec3& eye, const ares::dVec3& center, const ares::dVec3& up) const;

private:

  // enum used to access viewport attributes
  enum Vp
  {
    pos_x = 0, // pos x index in viewport array
    pos_y,     // pos y index in viewport array
    width,     // width index in viewport array
    height     // height index in viewport array
  };

  // Viewport position and size (x, y, width, height)
  int32_t _viewport[4] = {0};
  // Cached matrix used in various computations
  mutable ares::dMatrix _matrix1;
  // Cached matrix used in various computations
  mutable ares::dMatrix _matrix2;
};

} // namespace hera

#endif //__HERA_RENDERER_H__
