#ifndef __HERA_RENDERER_H__
#define __HERA_RENDERER_H__

#include "texture.h"

#include <ares/matrix.h>
#include <ares/vec3.h>
#include <array>

namespace hera
{

class Image;
class Glass_parts;
class Solid_parts;

class Renderer
{
public:

  /**
   * @brief Construct a new object
   */
  Renderer();

  /**
   * @brief Basic scene setup
   */
  void basic_scene_setup() const;

  /**
   * @brief Basic start scene setup, clears buffers, loads identity
   */
  void basic_start_scene() const;

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
  const ares::dvec3 un_project(double winx, double winy, double winz = 1) const;

  /**
   * @brief Define a view transform setting the "camera" eye position looking at center position
   * @param eye Position of the eye
   * @param center Position of the look at point
   * @param up Camera up
   */
  void look_at(const ares::dvec3& eye, const ares::dvec3& center, const ares::dvec3& up) const;

  /**
   * @brief Create a texture from image
   * @param img Image to use
   * @param min Minimization filter
   * @param mag Magnification filter
   * @return Created texture
   */
  Texture create_texture(const Image& img, Texture::Min min, Texture::Mag mag) const;

  /**
   * @brief Render the provided parts, solids (opaque) first then aquas (transparents)
   * @param solids Solid (opaque) parts
   * @param glassy Glassy (transparent) parts, must be sorted farthest to closest relative to the
   * viewer
   */
  void render_parts(const Solid_parts& solids, const Glass_parts& glassy);

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
  mutable ares::dmatrix _mx1;
  // Cached matrix used in various computations
  mutable ares::dmatrix _mx2;
  // filter enum
  std::array<int32_t, 6> _filter;
  // blend enum
  std::array<int32_t, 5> _blend;
};

} // namespace hera

#endif //__HERA_RENDERER_H__
