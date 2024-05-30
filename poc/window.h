#include <cstdint>
#include <memory>

class Window
{
public:

  struct Impl;

  /**
   * @brief Create the object
   * @param title Window title
   * @param width Window width
   * @param height Window height
   * @param bits Color bits 16/24/32
   */
  Window(const char* title, int32_t width, int32_t height, uint8_t bits);

  /**
   * @brief Destroy the object
   */
  ~Window();

  /**
   * @brief Swap window buffer at the end of a draw
   */
  void swap_buffers() const;

  /**
   * @brief Switch mode between fullscreen and windowed
   */
  void switch_fullscreen();

  /**
   * @brief Set fullscreen
   */
  void set_fullscreen();

  /**
   * @brief Set windowed
   */
  void set_windowed();

  /**
   * @brief Check if window is minimized
   * @return bool Result of check
   */
  bool is_minimized() const;

  /**
   * @brief Check if the window is valid
   * @return bool Result of check
   */
  bool is_valid() const;

private:

  // Window implementation
  std::unique_ptr<Impl> mimpl;
};
