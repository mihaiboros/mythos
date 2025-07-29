#include "../window.h"

#include "window_impl.h"

namespace hera
{

Window::Window() = default;
Window::~Window() = default;



void Window::set_impl(std::unique_ptr<Impl> impl)
{
  _impl = std::move(impl);
}



void Window::swap_buffers() const
{
  SwapBuffers(_impl->device_ctx);
}



void Window::switch_fullscreen()
{
  if (is_fullscreen)
  {
    set_windowed();
  }
  else
  {
    set_fullscreen();
  }
}



void Window::set_fullscreen()
{
  DWORD style = GetWindowLong(_impl->wnd_handle, GWL_STYLE);
  if (style & WS_OVERLAPPEDWINDOW)
  {
    MONITORINFO info = {sizeof(info)};
    if (GetWindowPlacement(_impl->wnd_handle, &_impl->placement)
        && GetMonitorInfo(MonitorFromWindow(_impl->wnd_handle, MONITOR_DEFAULTTOPRIMARY), &info))
    {
      SetWindowLong(_impl->wnd_handle, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
      SetWindowPos(_impl->wnd_handle,
        HWND_TOP,
        info.rcMonitor.left,
        info.rcMonitor.top,
        info.rcMonitor.right - info.rcMonitor.left,
        info.rcMonitor.bottom - info.rcMonitor.top,
        SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
      ShowCursor(FALSE);
      is_fullscreen = true;
    }
  }
}



void Window::set_windowed()
{
  DWORD style = GetWindowLong(_impl->wnd_handle, GWL_STYLE);
  if (!(style & WS_OVERLAPPEDWINDOW))
  {
    SetWindowLong(_impl->wnd_handle, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
    SetWindowPlacement(_impl->wnd_handle, &_impl->placement);
    SetWindowPos(_impl->wnd_handle,
      nullptr,
      0,
      0,
      0,
      0,
      SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    ShowCursor(TRUE);
    is_fullscreen = false;
  }
}

} // namespace hera
