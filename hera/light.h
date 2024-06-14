#ifndef __HERA_LIGHT_H__
#define __HERA_LIGHT_H__

#include "color.h"

#include <ares/vec3.h>

namespace hera
{

struct Light
{
  // light position
  ares::dVec3 pos;
  // light color
  Color color;
  // flag indicating ambiental light
  bool is_ambiental{false};
};

} // namespace hera

#endif //__HERA_LIGHT_H__
