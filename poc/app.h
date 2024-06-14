#ifndef __POC_APP_H__
#define __POC_APP_H__

#include "scene.h"

#include <hera/keymap.h>
#include <hera/window.h>

namespace poc
{

class App
{
public:

  /**
   * @brief Construct a new object
   * @param title Application title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   */
  App(const char* title, int32_t width, int32_t height, uint8_t bits);

  /**
   * @brief Check if the app window is valid
   * @return bool Result of check
   */
  bool is_valid() const;

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
   * @brief Execute one frame, handle input events, draw scene, etc
   */
  void execute_frame();

private:

  // App window
  hera::Window m_win;
  // App scene
  Scene m_scene;
  // App keyboard state
  hera::Keymap m_keys;
};



inline App::App(const char* title, int32_t width, int32_t height, uint8_t bits)
  : m_win(title, width, height, bits)
{
  m_scene.init(width, height);
}



inline bool App::is_valid() const
{
  return m_win.is_valid();
}



inline void App::load()
{
  m_scene.load();
}



inline void App::set_key(uint8_t key_code, bool is_pressed)
{
  m_keys[key_code] = is_pressed;
}



inline void App::resize(int32_t width, int32_t height)
{
  m_scene.resize(width, height);
}

} // namespace poc

#endif //__POC_APP_H__
