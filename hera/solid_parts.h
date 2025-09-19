#ifndef __HERA_SOLID_PARTS_H__
#define __HERA_SOLID_PARTS_H__

#include "texture.h"
#include "vertex.h"

#include <ares/matrix.h>
#include <span>
#include <vector>

namespace hera
{

/**
 * @brief Solid (opaque) 3D object parts collection
 */
class Solid_parts
{
public:

  struct Part
  {
    // texture
    Texture tex;
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
  };

  /**
   * @brief Add part
   * @param tex Part texture
   * @param cs Local cs
   */
  void add_part(Texture tex, const ares::dcs3& cs);

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
   * @brief Get the part at the provided index
   * @param index Index to use
   * @return Requested part
   */
  Part& get_part(int index);

  // Part const iterator
  struct Citer;

  /**
   * @brief Returns an iterator to the beginning of all faces
   * @return Begin iterator
   */
  Citer begin() const;

  /**
   * @brief Returns an iterator to the end of all faces
   * @return End iterator
   */
  Citer end() const;

private:

  // solid parts
  std::vector<Part> _parts;
  // solid faces
  std::vector<Face> _faces;
  // all vertices
  std::vector<Vertex> _vertices;
};



inline void Solid_parts::add_part(Texture tex, const ares::dcs3& cs)
{
  _parts.push_back({.tex = tex, .mat = ares::dmatrix::make_from(cs)});
}



inline void Solid_parts::add_face(
  const ares::fvec3& normal, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
  _faces.push_back(
    {.part = static_cast<int32_t>(_parts.size()) - 1,
     .norm = normal,
     .is_quad = false,
     .vbegin = static_cast<int32_t>(_vertices.size())});
  _vertices.insert(_vertices.end(), {v0, v1, v2});
}



inline void Solid_parts::add_face(
  const ares::fvec3& normal, const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
  _faces.push_back(
    {.part = static_cast<int32_t>(_parts.size()) - 1,
     .norm = normal,
     .is_quad = true,
     .vbegin = static_cast<int32_t>(_vertices.size())});
  _vertices.insert(_vertices.end(), {v0, v1, v2, v3});
}



inline Solid_parts::Part& Solid_parts::get_part(int index)
{
  return _parts[index];
}



struct Solid_parts::Citer
{
  // part begin iterator
  std::vector<Part>::const_iterator pbegin;
  // vertex begin iterator
  std::vector<Vertex>::const_iterator vbegin;
  // face iterator
  std::vector<Face>::const_iterator face_it;


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



inline Solid_parts::Citer Solid_parts::begin() const
{
  return {.pbegin = _parts.begin(), .vbegin = _vertices.begin(), .face_it = _faces.begin()};
}



inline Solid_parts::Citer Solid_parts::end() const
{
  return {.pbegin = _parts.begin(), .vbegin = _vertices.begin(), .face_it = _faces.end()};
}



inline bool Solid_parts::Citer::operator==(const Citer& other) const
{
  return face_it == other.face_it;
}



inline bool Solid_parts::Citer::operator!=(const Citer& other) const
{
  return !(*this == other);
}



inline std::tuple<const Solid_parts::Part&, const Solid_parts::Face&, std::span<const Vertex>>
Solid_parts::Citer::operator*()
{
  const auto part_it = pbegin + face_it->part;
  const auto vert_it = vbegin + face_it->vbegin;
  return {*part_it, *face_it, {vert_it, vert_it + 3 + face_it->is_quad}};
}



inline void Solid_parts::Citer::operator++()
{
  face_it++;
}

} // namespace hera

#endif //__HERA_SOLID_PARTS_H__
