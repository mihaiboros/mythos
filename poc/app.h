#ifndef __POC_APP_H__
#define __POC_APP_H__

#include "scene.h"

#include <hera/keymap.h>

namespace poc
{

class App
{
public:

  /**
   * @brief Construct a new object
   * @param width Window width
   * @param height Window height
   */
  App(int32_t width, int32_t height);

  /**
   * @brief Load the application
   */
  void load();

  /**
   * @brief Set key state
   * @param key_code System key code
   * @param is_pressed Indicates if key has been pressed or released
   */
  void set_key(uint8_t key_code, bool is_pressed);

  /**
   * @brief Resize the scene
   * @param width Scene width
   * @param height Scene height
   */
  void resize(int32_t width, int32_t height);

  /**
   * @brief Mouse move event
   * @param x Mouse window coordinate
   * @param y Mouse window coordinate
   */
  void mouse_move(int x, int y);

  /**
   * @brief Execute one frame, handle input events, draw scene, etc
   */
  void execute_frame();

private:

  // App scene
  Scene _scene;
  // App keyboard state
  hera::Keymap _keys;
};



inline App::App(int32_t width, int32_t height)
{
  _scene.init(width, height);
}



inline void App::load()
{
  _scene.load();
}



inline void App::set_key(uint8_t key_code, bool is_pressed)
{
  _keys.set_key(key_code, is_pressed);
}



inline void App::resize(int32_t width, int32_t height)
{
  _scene.resize(width, height);
}



inline void App::mouse_move(int32_t x, int32_t y)
{
  _scene.mouse_move(x, y);
}

} // namespace poc

#endif //__POC_APP_H__
