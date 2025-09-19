#include "../engine.h"
#include "window_impl.h"

namespace
{
// cached OS message variable
MSG msg;

/**
 * @brief Window message handler
 * @param wnd Window handle
 * @param msg Message to handle
 * @param wparam Message info
 * @param lparam Message info
 * @return LRESULT Result of operation
 */
LRESULT CALLBACK wndproc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

} // namespace

namespace hera
{

bool Engine::create_window(const char* title, int32_t width, int32_t height, uint8_t bits)
{
  renderer.set_viewport(0, 0, width, height);
  auto wimpl = Window::Impl::make_impl(title, width, height, bits, wndproc);
  const bool is_valid = wimpl != nullptr;
  window.set_impl(std::move(wimpl));
  return is_valid;
}



void Engine::show_cursor(bool show) const
{
  ShowCursor(show);
}



void Engine::set_cursor(int x, int y) const
{
  SetCursorPos(x, y);
}



bool Engine::peek_events_and_continue()
{
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
  {
    if (WM_QUIT == msg.message)
    {
      return false;
    }

    switch (msg.message)
    {
      case WM_KEYDOWN:
        on_key(static_cast<uint8_t>(msg.wParam), true);
        break;

      case WM_KEYUP:
        on_key(static_cast<uint8_t>(msg.wParam), false);
        break;

      case WM_MOUSEMOVE:
        POINT pt;
        GetCursorPos(&pt);
        on_mouse_move(pt.x, pt.y);
        break;

      default:
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        break;
    }
  }
  return true;
}

} // namespace hera

namespace
{

LRESULT CALLBACK wndproc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  bool is_handled = true;
  switch (msg)
  {
    case WM_ACTIVATE:
      hera::engine.window.is_minimized = HIWORD(wparam);
      break;

    case WM_SYSCOMMAND:
      is_handled = SC_SCREENSAVE == wparam || SC_MONITORPOWER == wparam;
      break;

    case WM_WINDOWPOSCHANGED:
      if (RECT rect; GetWindowRect(wnd, &rect))
      {
        const int32_t width = rect.right - rect.left;
        const int32_t height = rect.bottom - rect.top;
        hera::engine.window.width = width;
        hera::engine.window.height = height;
        hera::engine.on_resize(width, height);
        is_handled = true;
      }
      break;

    case WM_CLOSE:
      PostQuitMessage(0);
      break;

    default:
      is_handled = false;
      break;
  }

  return is_handled ? 0 : DefWindowProc(wnd, msg, wparam, lparam);
}

} // namespace
