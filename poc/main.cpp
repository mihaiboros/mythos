#include "keymap.h"
#include "window.h"

#include <gl/GL.h>
#include <gl/GLU.h>

void init()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0, 0, 0, 0);
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_EQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}



void resize(int width, int height)
{
  glViewport(0, 0, width, height > 0 ? height : 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, static_cast<double>(width) / height, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void draw(const Window& win)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  win.swap_buffers();
}



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
      draw(win);
    }

    if (keys[Key::F1])
    {
      keys[Key::F1] = false;
      win.switch_fullscreen();
    }
  }

  return static_cast<int>(msg.wParam);
}
