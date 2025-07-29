#include "window_impl.h"

namespace
{

constexpr const char* class_name = "OpenGL";

/**
 * @brief Make a pixel format descriptor for a window
 * @return PIXELFORMATDESCRIPTOR
 */
constexpr PIXELFORMATDESCRIPTOR make_pfd();

/**
 * @brief Window message handler on exit
 * @param wnd Window handle
 * @param msg Message to handle
 * @param wparam Message info
 * @param lparam Message info
 * @return LRESULT Result of operation
 */
LRESULT CALLBACK wndexit(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

} // namespace


namespace hera
{

std::unique_ptr<Window::Impl> Window::Impl::make_impl(
  const char* title, int32_t width, int32_t height, uint8_t bits, WNDPROC wndproc)
{
  std::unique_ptr<Window::Impl> w = std::make_unique<Window::Impl>();
  w->inst = GetModuleHandle(nullptr);

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = wndproc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = w->inst;
  wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = nullptr;
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = class_name;
  if (!RegisterClass(&wc))
  {
    return nullptr;
  }

  RECT rect{.left = 0, .top = 0, .right = width, .bottom = height};
  DWORD style = WS_OVERLAPPEDWINDOW;
  DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  AdjustWindowRectEx(&rect, style, FALSE, ex_style);

  w->wnd_handle = CreateWindowEx(ex_style,
    class_name,
    title,
    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style,
    0,
    0,
    rect.right - rect.left,
    rect.bottom - rect.top,
    nullptr,
    nullptr,
    w->inst,
    nullptr);
  if (!w->wnd_handle)
  {
    return nullptr;
  }

  w->device_ctx = GetDC(w->wnd_handle);
  if (!w->device_ctx)
  {
    return nullptr;
  }

  w->pfd.cColorBits = bits;
  uint32_t pixel_format = ChoosePixelFormat(w->device_ctx, &w->pfd);
  if (0 == pixel_format || !SetPixelFormat(w->device_ctx, pixel_format, &w->pfd))
  {
    return nullptr;
  }

  w->render_ctx = wglCreateContext(w->device_ctx);
  if (!w->render_ctx || !wglMakeCurrent(w->device_ctx, w->render_ctx))
  {
    return nullptr;
  }

  ShowWindow(w->wnd_handle, SW_SHOW);
  SetForegroundWindow(w->wnd_handle);
  SetFocus(w->wnd_handle);
  return w;
}



Window::Impl::Impl() : pfd{make_pfd()}
{
}



Window::Impl::~Impl()
{
  if (render_ctx)
  {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(render_ctx);
    render_ctx = nullptr;
  }

  if (device_ctx)
  {
    ReleaseDC(wnd_handle, device_ctx);
    device_ctx = nullptr;
  }

  if (wnd_handle)
  {
    SetWindowLongPtrA(wnd_handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndexit));
    DestroyWindow(wnd_handle);
    wnd_handle = nullptr;
  }

  if (inst)
  {
    UnregisterClass(class_name, inst);
    inst = nullptr;
  }
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



LRESULT CALLBACK wndexit(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return DefWindowProc(wnd, msg, wparam, lparam);
}

} // namespace
