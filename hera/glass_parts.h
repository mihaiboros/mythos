#ifndef __HERA_GLASSY_PARTS_H__
#define __HERA_GLASSY_PARTS_H__

#include "blend.h"
#include "texture.h"
#include "vertex.h"

#include <ares/matrix.h>
#include <span>
#include <vector>

namespace hera
{

/**
 * @brief Glass (transparent) 3D object parts collection (use sort before rendering)
 */
class Glass_parts
{
public:

  struct Part
  {
    // texture
    Texture tex;
    // blend params
    Blend blend;
    // matrix from object local cs
    ares::dmatrix mat;
  };

  struct Face
  {
    // object part that this face belongs to
    int32_t part{0};
    // face normal
    ares::fvec3 norm;
    // face is quad and has 4 vertices, else 3
    bool is_quad{false};
    // vertex begin index
    int32_t vbegin{0};
    // mid (center) point in world cs
    ares::dvec3 wcs_mid;
  };

  /**
   * @brief Add part
   * @param tex Part texture
   * @param blend Blend parameters
   * @param cs Local cs
   */
  void add_part(Texture tex, Blend blend, const ares::dcs3& cs);

  /**
   * @brief Add a face for the last added part
   * @param normal Face normal
   * @param v0 Face vertex
   * @param v1 Face vertex
   * @param v2 Face vertex
   */
  void add_face(const ares::fvec3& normal, const Vertex& v0, const Vertex& v1, const Vertex& v2);

  /**
   * @brief Add a face for the last added part
   * @param normal Face normal
   * @param v0 Face vertex
   * @param v1 Face vertex
   * @param v2 Face vertex
   * @param v3 Face vertex
   */
  void add_face(
    const ares::fvec3& normal,
    const Vertex& v0,
    const Vertex& v1,
    const Vertex& v2,
    const Vertex& v3);

  /**
   * @brief Sort render order by depth along the provided vector direction, farthest to closest
   * @param dir Direction to use
   */
  void sort_by_depth(const ares::dvec3& dir);

  // Part const iterator
  struct Citer;

  /**
   * @brief Returns an iterator to the beginning of all faces in render order
   * @return Begin iterator
   */
  Citer begin() const;

  /**
   * @brief Returns an iterator to the end of all faces in render order
   * @return End iterator
   */
  Citer end() const;

private:

  // aqua parts
  std::vector<Part> _parts;
  // aqua faces
  std::vector<Face> _faces;
  // all vertices
  std::vector<Vertex> _vertices;
  // render order
  std::vector<int32_t> _order;
};



inline void Glass_parts::add_part(Texture tex, Blend blend, const ares::dcs3& cs)
{
  _parts.push_back({.tex = tex, .blend = blend, .mat = ares::dmatrix::make_from(cs)});
}



inline void Glass_parts::add_face(
  const ares::fvec3& normal, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
  _faces.push_back(
    {.part = static_cast<int32_t>(_parts.size()) - 1,
     .norm = normal,
     .is_quad = false,
     .vbegin = static_cast<int32_t>(_vertices.size()),
     .wcs_mid = _parts.back().mat.transform_p((v0.pos + v1.pos + v2.pos) / 3)});
  _order.push_back(static_cast<int32_t>(_faces.size()) - 1);
  _vertices.insert(_vertices.end(), {v0, v1, v2});
}



inline void Glass_parts::add_face(
  const ares::fvec3& normal, const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
  _faces.push_back(
    {.part = static_cast<int32_t>(_parts.size()) - 1,
     .norm = normal,
     .is_quad = true,
     .vbegin = static_cast<int32_t>(_vertices.size()),
     .wcs_mid = _parts.back().mat.transform_p((v0.pos + v1.pos + v2.pos + v3.pos) / 4)});
  _order.push_back(static_cast<int32_t>(_faces.size()) - 1);
  _vertices.insert(_vertices.end(), {v0, v1, v2, v3});
}



inline void Glass_parts::sort_by_depth(const ares::dvec3& dir)
{
  const auto cmp = [&dir, this](int32_t el1, int32_t el2)
  { return _faces[el1].wcs_mid.dot(dir) > _faces[el2].wcs_mid.dot(dir); };
  std::sort(_order.begin(), _order.end(), cmp);
}



struct Glass_parts::Citer
{
  // part begin iterator
  std::vector<Part>::const_iterator pbegin;
  // face begin iterator
  std::vector<Face>::const_iterator fbegin;
  // vertex begin iterator
  std::vector<Vertex>::const_iterator vbegin;
  // order iterator
  std::vector<int32_t>::const_iterator order_it;

  /**
   * @brief Equality operator
   * @param other Object to compare against
   * @return Result of comparison
   */
  bool operator==(const Citer& other) const;

  /**
   * @brief Inequality operator
   * @param other Object to compare against
   * @return Result of comparison
   */
  bool operator!=(const Citer& other) const;

  /**
   * @brief Deref operator
   * @return Face and vertices
   */
  std::tuple<const Part&, const Face&, std::span<const Vertex>> operator*();

  /**
   * @brief Increment operator
   */
  void operator++();
};



inline Glass_parts::Citer Glass_parts::begin() const
{
  return {
    .pbegin = _parts.begin(),
    .fbegin = _faces.begin(),
    .vbegin = _vertices.begin(),
    .order_it = _order.begin()};
}



inline Glass_parts::Citer Glass_parts::end() const
{
  return {
    .pbegin = _parts.begin(),
    .fbegin = _faces.begin(),
    .vbegin = _vertices.begin(),
    .order_it = _order.end()};
}



inline bool Glass_parts::Citer::operator==(const Citer& other) const
{
  return order_it == other.order_it;
}



inline bool Glass_parts::Citer::operator!=(const Citer& other) const
{
  return !(*this == other);
}



inline std::tuple<const Glass_parts::Part&, const Glass_parts::Face&, std::span<const Vertex>>
Glass_parts::Citer::operator*()
{
  const auto face_it = fbegin + *order_it;
  const auto part_it = pbegin + face_it->part;
  const auto vert_it = vbegin + face_it->vbegin;
  return {*part_it, *face_it, {vert_it, vert_it + 3 + face_it->is_quad}};
}



inline void Glass_parts::Citer::operator++()
{
  order_it++;
}

} // namespace hera

#endif //__HERA_GLASSY_PARTS_H__
