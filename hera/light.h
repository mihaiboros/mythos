#ifndef __HERA_LIGHT_H__
#define __HERA_LIGHT_H__

#include "color.h"

#include <ares/vec3.h>

namespace hera
{

struct Light
{
  // light position
  ares::fVec3 pos;
  // ambient light
  fColor ambient;
  // diffuse light
  fColor diffuse;
};

} // namespace hera

#endif //__HERA_LIGHT_H__
