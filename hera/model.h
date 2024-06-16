#ifndef __HERA_MODEL_H__
#define __HERA_MODEL_H__

#include "color.h"
#include "vertex.h"

#include <ares/ccs3.h>
#include <array>
#include <vector>

namespace hera
{

template <bool Quads> struct Model;

using tModel = Model<false>;
using qModel = Model<true>;

template <bool Quads> struct Model
{
  struct Face
  {
    // face normal
    ares::dVec3 normal;
    // face vertices in local coordinates
    std::array<Vertex, Quads ? 4 : 3> vertices;
  };

  // local coordinate system
  ares::dCcs3 cs;
  // model faces
  std::vector<Face> faces;
};

} // namespace hera

#endif //__HERA_MODEL_H__
