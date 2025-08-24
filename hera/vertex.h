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
  ares::dvec3 pos;
  // vertex color
  ubColor color{.r = 255, .g = 255, .b = 255, .a = 255};
  // texture coord
  ares::dvec2 tex;
};

} // namespace hera

#endif //__HERA_VERTEX_H__
