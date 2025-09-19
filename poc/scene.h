#ifndef __POC_SCENE_H__
#define __POC_SCENE_H__

#include <cstdint>
#include <hera/camera.h>
#include <hera/glass_parts.h>
#include <hera/keymap.h>
#include <hera/light.h>
#include <hera/solid_parts.h>
#include <hera/time/animation.h>

namespace poc
{

class Scene
{
public:

  /**
   * @brief Initialize the scene
   * @param width Scene width
   * @param height Scene height
   */
  void init(int32_t width, int32_t height);

  /**
   * @brief Resize the scene
   * @param width Scene width
   * @param height Scene height
   */
  void resize(int32_t width, int32_t height);

  /**
   * @brief Handle mouse move events
   * @param x Cursor x position
   * @param y Cursor y position
   */
  void mouse_move(int x, int y);

  /**
   * @brief Load the scene
   */
  void load();

  /**
   * @brief Handle key events
   * @param keys Key map to use
   */
  void handle_keys(hera::Keymap& keys);

  /**
   * @brief Render the scene
   */
  void render();

private:

  // object parts
  hera::Glass_parts _glassy;
  hera::Solid_parts _solids;
  // light
  bool _has_light{false};
  hera::Light _light;
  // World camera
  hera::Camera _camera;
  // Animation
  hera::Animation _ani;
};

} // namespace poc

#endif //__POC_SCENE_H__
