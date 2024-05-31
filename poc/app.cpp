#include "app.h"

namespace poc
{

void App::execute_frame()
{
  if (mkeys[Key::F1])
  {
    mkeys[Key::F1] = false;
    mwin.switch_fullscreen();
  }

  if (!mwin.is_minimized())
  {
    mscene.draw();
    mwin.swap_buffers();
  }
}

} // namespace poc
