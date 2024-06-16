#include "app.h"

namespace poc
{

using hera::Key;

void App::execute_frame()
{
  if (m_keys[Key::F1])
  {
    m_keys[Key::F1] = false;
    m_win.switch_fullscreen();
  }

  if (!m_win.is_minimized())
  {
    m_scene.handle_keys(m_keys);
    m_scene.draw();
    m_win.swap_buffers();
  }
}

} // namespace poc
