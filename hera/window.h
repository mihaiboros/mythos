#ifndef __HERA_WINDOW_H__
#define __HERA_WINDOW_H__

#include <cstdint>
#include <memory>

namespace hera
{

class Window
{
public:

  // window os specific implementation
  struct Impl;

  /**
   * @brief Create the object
   */
  Window();

  /**
   * @brief Destroy the object
   */
  ~Window();

  /**
   * @brief Set the window implemetnation
   * @param impl Implemetnation to set
   */
  void set_impl(std::unique_ptr<Impl> impl);

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

  // window is minimized
  bool is_minimized{false};
  // window is fullscreen
  bool is_fullscreen{false};
  // window actual width
  int32_t width{0};
  // window actual height
  int32_t height{0};

private:

  // Window implementation
  std::unique_ptr<Impl> _impl;
};

} // namespace hera

#endif //__HERA_WINDOW_H__
