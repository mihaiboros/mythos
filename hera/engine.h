#ifndef __HERA_ENGINE_H__
#define __HERA_ENGINE_H__

#include "camera.h"
#include "renderer.h"
#include "time/scheduler.h"
#include "window.h"

#include <functional>
#include <memory>

namespace hera
{

class Engine
{
  friend std::unique_ptr<Engine> std::make_unique<Engine>();

public:

  /**
   * @brief Get engine instance
   * @return Engine instance
   */
  static Engine& instance();

  /**
   * @brief Create the window
   * @param title Window title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   * @return Result of operation
   */
  bool create_window(const char* title, int32_t width, int32_t height, uint8_t bits);

  /**
   * @brief Execute engine main loop
   * @return False to exit
   */
  bool main_loop();

  /**
   * @brief Point camera at the specified window coordinates
   * @param cam Camera to point
   * @param winx X window coordinate to be mapped
   * @param winy Y window coordinate to be mapped
   */
  void point_camera(Camera& cam, int32_t winx, int32_t winy);

  /**
   * @brief Set camera in scene
   * @param cam Camera to set
   */
  void set_camera(const Camera& cam);

  /**
   * @brief Show or hide the mouse cursor
   * @param show Flag to show or hide the cursor
   */
  void show_cursor(bool show) const;

  // key event handler
  std::function<void(uint8_t key, bool is_pressed)> on_key;
  // resize event handler
  std::function<void(int32_t width, int32_t height)> on_resize;
  // mouse move event handler
  std::function<void(int32_t x, int32_t y)> on_mouse_move;
  // application window
  Window window;
  // renderer
  Renderer renderer;
  // time scheduler
  Scheduler scheduler;

private:

  /**
   * @brief Construct a new object
   */
  Engine();

  /**
   * @brief Set cursor position
   * @param x Position to set
   * @param y Position to set
   */
  void set_cursor(int32_t x, int32_t y) const;

  /**
   * @brief Peek OS events and continue if no quit received
   * @return false on quit, true to continue
   */
  bool peek_events_and_continue();

  // singleton engine instance
  inline static std::unique_ptr<Engine> _inst{std::make_unique<Engine>()};
  // mouse windows coordinates
  ares::ivec2 _win_coords;
};

static Engine& engine{Engine::instance()};



inline Engine& Engine::instance()
{
  return *_inst;
}



inline bool Engine::main_loop()
{
  scheduler.run();
  return peek_events_and_continue();
}



inline void Engine::point_camera(Camera& cam, int32_t winx, int32_t winy)
{
  if (_win_coords.x != winx || _win_coords.y != winy)
  {
    _win_coords.x = winx;
    _win_coords.y = winy;
    const auto pos = renderer.un_project(winx, winy, 1);
    cam.point_at(pos);
    set_cursor(cam.center.x, cam.center.y);
  }
}



inline void Engine::set_camera(const Camera& cam)
{
  renderer.look_at(cam.position(), cam.position() + cam.cs().x_axis, cam.cs().y_axis);
}

} // namespace hera

#endif //__HERA_ENGINE_H__
