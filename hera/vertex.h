#ifndef __HERA_VERTEX_H__
#define __HERA_VERTEX_H__

#include "color.h"

#include <ares/vec2.h>
#include <ares/vec3.h>

namespace hera
{

struct Vertex
{
  // vertex position
  ares::dVec3 pos;
  // vertex color
  ubColor color;
  // texture coord
  ares::dVec2 tex;
};

} // namespace hera

#endif //__HERA_VERTEX_H__
