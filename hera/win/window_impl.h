#ifndef __HERA_WINDOW_IMPL_H__
#define __HERA_WINDOW_IMPL_H__

#include "../window.h"

#include <Windows.h>

namespace hera
{

struct Window::Impl
{
  /**
   * @brief Create the window implementation
   * @param title Window title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   * @param wndproc Window processing function
   * @return Window implementation, null if failed
   */
  static std::unique_ptr<Impl> make_impl(
    const char* title, int32_t width, int32_t height, uint8_t bits, WNDPROC wndproc);

  /**
   * @brief Construct a new object
   */
  Impl();

  /**
   * @brief Destroy the object
   */
  ~Impl();

  // Permanent rendering context
  HGLRC render_ctx = nullptr;
  // Private GDI device context
  HDC device_ctx = nullptr;
  // Window handle
  HWND wnd_handle = nullptr;
  // Application instance
  HINSTANCE inst = nullptr;
  // Pixel format
  PIXELFORMATDESCRIPTOR pfd;
  // Window placement
  WINDOWPLACEMENT placement = {sizeof(placement)};
};

} // namespace hera

#endif //__HERA_WINDOW_IMPL_H__
