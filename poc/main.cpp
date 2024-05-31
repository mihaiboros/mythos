#include "app.h"

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
  poc::App app("POC", 800, 600, 16);

  MSG msg;
  while (app.is_valid())
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      if (WM_QUIT == msg.message)
      {
        break;
      }

      switch (msg.message)
      {
        case WM_KEYDOWN:
          app.set_key(static_cast<uint8_t>(msg.wParam), true);
          break;

        case WM_KEYUP:
          app.set_key(static_cast<uint8_t>(msg.wParam), false);
          break;

        case WM_SIZE:
          app.resize(LOWORD(msg.lParam), HIWORD(msg.lParam));
          break;

        default:
          TranslateMessage(&msg);
          DispatchMessage(&msg);
          break;
      }
    }

    app.execute_frame();
  }

  return static_cast<int>(msg.wParam);
}
