#include "app.h"

#include <hera/engine.h>
#include <Windows.h>

/**
 * @brief App entry point
 * @param inst
 * @param prev_inst
 * @param cmd_line
 * @param cmd_show
 * @return int App result
 */
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev_inst, LPSTR cmd_line, int cmd_show)
{
  if (!hera::engine.create_window("POC", 800, 600, 16))
  {
    return 1;
  }

  poc::App app(hera::engine.window.width, hera::engine.window.height);
  hera::engine.on_key = [&app](uint8_t key, bool key_down) { app.set_key(key, key_down); };
  hera::engine.on_resize = [&app](int32_t width, int32_t height) { app.resize(width, height); };

  app.load();
  while (hera::engine.peek_events_and_continue())
  {
    app.execute_frame();
  }

  return 0;
}
