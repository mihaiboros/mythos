#include "window.h"

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
  MSG msg;
  Window* win = Window::create_once("POC", 800, 600, 16, false);

  while (win)
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      if (WM_QUIT == msg.message)
      {
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    if (!win->is_minimized())
    {
      win->draw();
    }
  }

  delete win;
  return static_cast<int>(msg.wParam);
}
