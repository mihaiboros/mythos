#include <cstdint>
#include <Windows.h>

class Window
{
public:

  /**
   * @brief Create the window
   * @param title Window title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   * @param is_fullscreen Flag indicating if window should be fullscreen
   * @return Window* Created window
   */
  static Window* create_once(
    const char* title, int width, int height, uint8_t bits, bool is_fullscreen);

  /**
   * @brief Window message handler
   * @param wnd Window handle
   * @param msg Message to handle
   * @param wparam Message info
   * @param lparam Message info
   * @return LRESULT Result of operation
   */
  static LRESULT CALLBACK wndproc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

  /**
   * @brief Destroy the object
   */
  ~Window();

  /**
   * @brief Resize window and scene
   * @param width Window width
   * @param height Window height
   */
  void resize(int width, int height);

  /**
   * @brief Draw the scene
   */
  void draw();

  /**
   * @brief Check if window is minimized
   * @return bool Result of check
   */
  bool is_minimized() const;

private:

  /**
   * @brief Construct a new object
   */
  Window() = default;

  /**
   * @brief Create the window
   * @param title Window title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   * @param is_fullscreen Flag indicating if window should be fullscreen
   * @return bool Result of operation
   */
  bool create(const char* title, int width, int height, uint8_t bits, bool is_fullscreen);

  /**
   * @brief Initialize the scene
   * @return bool Result of operation
   */
  bool init();

  // Permanent rendering context
  HGLRC m_rc = nullptr;
  // Private GDI device context
  HDC m_dc = nullptr;
  // Window handle
  HWND m_wnd = nullptr;
  // Application instance
  HINSTANCE m_inst = nullptr;
  // Minimized to taskbar
  bool m_is_minimized = false;
  // Window in fullscreen
  bool m_is_fullscreen = false;
};
