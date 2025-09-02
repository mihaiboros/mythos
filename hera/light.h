#ifndef __HERA_LIGHT_H__
#define __HERA_LIGHT_H__

#include "color.h"

#include <ares/vec3.h>

namespace hera
{

struct Light
{
  // light position
  ares::fvec3 pos;
  // ambient light
  fColor ambient;
  // diffuse light
  fColor diffuse;
  // specular light
  fColor specular;
  // light id
  int32_t id{0};
};

} // namespace hera

#endif //__HERA_LIGHT_H__
