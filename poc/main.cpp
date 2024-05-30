#include "keymap.h"
#include "scene.h"
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
  Keymap keys;
  Window win("POC", 800, 600, 16);
  resize(800, 600);
  init();

  MSG msg;
  while (win.is_valid())
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
          keys[static_cast<uint8_t>(msg.wParam)] = true;
          break;

        case WM_KEYUP:
          keys[static_cast<uint8_t>(msg.wParam)] = false;
          break;

        case WM_SIZE:
          resize(LOWORD(msg.lParam), HIWORD(msg.lParam));
          break;

        default:
          TranslateMessage(&msg);
          DispatchMessage(&msg);
          break;
      }
    }

    if (!win.is_minimized())
    {
      draw();
      win.swap_buffers();
    }

    if (keys[Key::F1])
    {
      keys[Key::F1] = false;
      win.switch_fullscreen();
    }
  }

  return static_cast<int>(msg.wParam);
}
