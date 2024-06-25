#ifndef __HERA_WORLD_H__
#define __HERA_WORLD_H__

#include "../model.h"

#include <span>

namespace hera
{

class World
{
public:

  /**
   * @brief Render models
   * @param opaques Opaque models
   * @param transparents Transparent models, should be sorted farthest to closest
   */
  void render(std::span<const Model> opaques, std::span<const Model> transparents);

private:
};

} // namespace hera

#endif //__HERA_WORLD_H__
