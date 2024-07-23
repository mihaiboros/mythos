#ifndef __HERA_WORLD_H__
#define __HERA_WORLD_H__

#include "../model.h"
#include "enums.h"

#include <span>

namespace hera
{

class World
{
public:

  /**
   * @brief Set the blend factors
   * @param src Source factor
   * @param dst Destination factor
   */
  void set_blend_factors(Blend src, Blend dst);

  /**
   * @brief Render models
   * @param opaques Opaque models
   * @param transparents Transparent models, should be sorted farthest to closest
   */
  void render(std::span<const Model> opaques, std::span<const Model> transparents);

private:
};



inline void World::set_blend_factors(Blend src, Blend dst)
{
  glBlendFunc(static_cast<GLenum>(src), static_cast<GLenum>(dst));
}

} // namespace hera

#endif //__HERA_WORLD_H__
