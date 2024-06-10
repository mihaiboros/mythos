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
  // local coordinate system
  ares::dccs3 cs;
  // model vertices in local coordinates
  std::vector<Vertex> vertices;
};

} // namespace hera

#endif //__HERA_MODEL_H__
