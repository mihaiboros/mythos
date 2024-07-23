#include "world.h"

namespace hera
{

void World::render(std::span<const Model> opaques, std::span<const Model> transparents)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const auto& el : opaques)
  {
    if (el.tex != 0)
    {
      el.bind_texture();
      el.render_textured(0, 0, 0);
    }
    else
    {
      el.render_colored(0, 0, 0);
    }
  }

  glEnable(GL_BLEND);
  for (const auto& el : transparents)
  {
    if (el.tex != 0)
    {
      el.bind_texture();
      el.render_textured(0, 0, 0);
    }
    else
    {
      el.render_colored(0, 0, 0);
    }
  }
  glDisable(GL_BLEND);
}

} // namespace hera
