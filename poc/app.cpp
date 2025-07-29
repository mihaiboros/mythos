#include "app.h"

#include <hera/engine.h>

namespace
{

// ignore mouse move events
void ignore_mouse_move(int32_t, int32_t) {};

} // namespace

namespace poc
{

using hera::Key;

void App::execute_frame()
{
  if (_keys.is_pressed(Key::F1))
  {
    _keys.release(Key::F1);
    if (auto& window = hera::engine.window; window.is_fullscreen)
    {
      window.set_windowed();
      hera::engine.show_cursor(true);
      hera::engine.on_mouse_move = ignore_mouse_move;
    }
    else
    {
      hera::engine.show_cursor(false);
      window.set_fullscreen();
      hera::engine.on_mouse_move = [this](int32_t x, int32_t y) { this->mouse_move(x, y); };
    }
  }

  if (!hera::engine.window.is_minimized)
  {
    _scene.handle_keys(_keys);
    _scene.draw();
    hera::engine.window.swap_buffers();
  }
}

} // namespace poc
