#ifndef __HERA_MODEL_H__
#define __HERA_MODEL_H__

#include "color.h"
#include "vertex.h"

#include <ares/cs3.h>
#include <vector>

namespace hera
{

struct Model
{
  struct Face
  {
    // face normal
    ares::dVec3 normal;
  };

  /**
   * @brief Render model with color
   * @param xr Rotation around x axis
   * @param yr Rotation around y axis
   * @param zr Rotation around z axis
   */
  void render_colored(double xr, double yr, double zr) const;

  /**
   * @brief Render model with texture
   * @param xr Rotation around x axis
   * @param yr Rotation around y axis
   * @param zr Rotation around z axis
   */
  void render_textured(double xr, double yr, double zr) const;

  /**
   * @brief Bind texture for use
   */
  void bind_texture() const;

  // local coordinate system
  ares::dCs3 cs;
  // model vertices
  std::vector<Vertex> vertices;
  // model faces
  std::vector<Face> faces;
  // model texture id
  uint32_t tex{0};
  // model has quad or triangle faces
  bool has_quads{false};
  // model has transparency
  bool is_transparent{false};
};

} // namespace hera

#endif //__HERA_MODEL_H__
