#ifndef __HERA_MODEL_H__
#define __HERA_MODEL_H__

#include "color.h"
#include "vertex.h"

#include <ares/ccs3.h>
#include <vector>

namespace hera
{

struct Model
{
  // model out of triangles or quads
  bool has_quads{false};
  // local coordinate system
  ares::dCcs3 cs;
  // model vertices in local coordinates
  std::vector<Vertex> vertices;
};

} // namespace hera

#endif //__HERA_MODEL_H__
