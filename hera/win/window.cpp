#include "../window.h"

#include <Windows.h>

namespace
{

constexpr const char* class_name = "OpenGL";
hera::Window::Impl* win = nullptr;

/**
 * @brief Make a pixel format descriptor for a window
 * @return PIXELFORMATDESCRIPTOR
 */
constexpr PIXELFORMATDESCRIPTOR make_pfd();

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

struct Window::Impl
{
  /**
   * @brief Construct a new object
   */
  Impl() = default;

  /**
   * @brief Destroy the object
   */
  ~Impl();

  /**
   * @brief Create the window
   * @param title Window title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   * @return bool Result of operation
   */
  bool create(const char* title, int32_t width, int32_t height, uint8_t bits);

  /**
   * @brief Release window and resources
   */
  void release();

  // Minimized to taskbar
  bool is_minimized = false;
  // Window in fullscreen
  bool is_fullscreen = false;

  // Permanent rendering context
  HGLRC rc = nullptr;
  // Private GDI device context
  HDC dc = nullptr;
  // Window handle
  HWND wnd = nullptr;
  // Application instance
  HINSTANCE inst = nullptr;
  // Pixel format
  PIXELFORMATDESCRIPTOR pfd = make_pfd();
  // Window placement
  WINDOWPLACEMENT placement = {sizeof(placement)};
};



inline Window::Impl::~Impl()
{
  release();
}



bool Window::Impl::create(const char* title, int32_t width, int32_t height, uint8_t bits)
{
  uint32_t pixel_format = 0;
  WNDCLASS wc;
  DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD style = WS_OVERLAPPEDWINDOW;

  RECT rect{.left = 0, .top = 0, .right = width, .bottom = height};

  inst = GetModuleHandle(nullptr);
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = wndproc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = inst;
  wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = nullptr;
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = class_name;

  if (!RegisterClass(&wc))
  {
    return false;
  }

  AdjustWindowRectEx(&rect, style, FALSE, ex_style);

  wnd = CreateWindowEx(ex_style,
    class_name,
    title,
    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style,
    0,
    0,
    rect.right - rect.left,
    rect.bottom - rect.top,
    nullptr,
    nullptr,
    inst,
    nullptr);

  if (!wnd)
  {
    return false;
  }

  dc = GetDC(wnd);
  if (!dc)
  {
    return false;
  }

  pfd.cColorBits = bits;
  pixel_format = ChoosePixelFormat(dc, &pfd);
  if (0 == pixel_format)
  {
    return false;
  }

  if (!SetPixelFormat(dc, pixel_format, &pfd))
  {
    return false;
  }

  rc = wglCreateContext(dc);
  if (!rc)
  {
    return false;
  }

  if (!wglMakeCurrent(dc, rc))
  {
    return false;
  }

  ShowWindow(wnd, SW_SHOW);
  SetForegroundWindow(wnd);
  SetFocus(wnd);

  return true;
}



void Window::Impl::release()
{
  if (rc)
  {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(rc);
    rc = nullptr;
  }

  if (dc)
  {
    ReleaseDC(wnd, dc);
    dc = nullptr;
  }

  if (wnd)
  {
    DestroyWindow(wnd);
    wnd = nullptr;
  }

  if (inst)
  {
    UnregisterClass(class_name, inst);
    inst = nullptr;
  }

  if (this == win)
  {
    win = nullptr;
  }
}



Window::Window(const char* title, int32_t width, int32_t height, uint8_t bits)
  : m_impl(std::make_unique<Impl>())
{
  if (m_impl->create(title, width, height, bits))
  {
    win = m_impl.get();
  }
  else
  {
    m_impl->release();
  }
}



Window::~Window() = default;



void Window::swap_buffers() const
{
  SwapBuffers(m_impl->dc);
}



void Window::switch_fullscreen()
{
  if (m_impl->is_fullscreen)
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
  DWORD style = GetWindowLong(m_impl->wnd, GWL_STYLE);
  if (style & WS_OVERLAPPEDWINDOW)
  {
    MONITORINFO info = {sizeof(info)};
    if (GetWindowPlacement(m_impl->wnd, &m_impl->placement)
        && GetMonitorInfo(MonitorFromWindow(m_impl->wnd, MONITOR_DEFAULTTOPRIMARY), &info))
    {
      SetWindowLong(m_impl->wnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
      SetWindowPos(m_impl->wnd,
        HWND_TOP,
        info.rcMonitor.left,
        info.rcMonitor.top,
        info.rcMonitor.right - info.rcMonitor.left,
        info.rcMonitor.bottom - info.rcMonitor.top,
        SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
      ShowCursor(FALSE);
      m_impl->is_fullscreen = true;
    }
  }
}



void Window::set_windowed()
{
  DWORD style = GetWindowLong(m_impl->wnd, GWL_STYLE);
  if (!(style & WS_OVERLAPPEDWINDOW))
  {
    SetWindowLong(m_impl->wnd, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
    SetWindowPlacement(m_impl->wnd, &m_impl->placement);
    SetWindowPos(m_impl->wnd,
      nullptr,
      0,
      0,
      0,
      0,
      SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    ShowCursor(TRUE);
    m_impl->is_fullscreen = false;
  }
}



bool Window::is_minimized() const
{
  return m_impl->is_minimized;
}



bool Window::is_valid() const
{
  return m_impl.get() == win;
}

} // namespace hera



namespace
{

constexpr PIXELFORMATDESCRIPTOR make_pfd()
{
  return {.nSize = sizeof(PIXELFORMATDESCRIPTOR),
    .nVersion = 1,
    .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    .iPixelType = PFD_TYPE_RGBA,
    .cColorBits = 0,
    .cRedBits = 0,
    .cRedShift = 0,
    .cGreenBits = 0,
    .cGreenShift = 0,
    .cBlueBits = 0,
    .cBlueShift = 0,
    .cAlphaBits = 0,
    .cAlphaShift = 0,
    .cAccumBits = 0,
    .cAccumRedBits = 0,
    .cAccumGreenBits = 0,
    .cAccumBlueBits = 0,
    .cAccumAlphaBits = 0,
    .cDepthBits = 16,
    .cStencilBits = 0,
    .cAuxBuffers = 0,
    .iLayerType = PFD_MAIN_PLANE,
    .bReserved = 0,
    .dwLayerMask = 0,
    .dwVisibleMask = 0,
    .dwDamageMask = 0};
}



LRESULT CALLBACK wndproc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if (!win)
  {
    return DefWindowProc(wnd, msg, wparam, lparam);
  }

  bool is_handled = true;
  switch (msg)
  {
    case WM_ACTIVATE:
      win->is_minimized = HIWORD(wparam);
      break;

    case WM_SYSCOMMAND:
      is_handled = SC_SCREENSAVE == wparam || SC_MONITORPOWER == wparam;
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
