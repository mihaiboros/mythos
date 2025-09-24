#ifndef __ARES_CURVE3D_H__
#define __ARES_CURVE3D_H__

#include "../vec3.h"

namespace ares
{

/**
 * @brief Geometric 3D curve
 */
class Curve3d
{
public:

  struct Params
  {
    dvec3 position;
    dvec3 tangent;
  };

  /**
   * @brief Construct a new object
   * @param start Curve start
   * @param end Curve end
   */
  Curve3d(const dvec3& start, const dvec3& end);

  /**
   * @brief Destroy the object
   */
  virtual ~Curve3d() = default;

  /**
   * @brief Get start point
   * @return Start point
   */
  const dvec3& start() const;

  /**
   * @brief Get end point
   * @return End point
   */
  const dvec3& end() const;

  /**
   * @brief Get the curve length
   * @return Length
   */
  double length() const;

  /**
   * @brief Compute position at curve progress
   * @param progress Progress to use in [0, 1] interval
   * @return Position at progress
   */
  virtual dvec3 position_at(double progress) const = 0;

  /**
   * @brief Compute tangent at curve progress
   * @param progress Progress to use in [0, 1] interval
   * @return Tangent at progress
   */
  virtual dvec3 tangent_at(double progress) const = 0;

  /**
   * @brief Compute curve parameters at progress
   * @param progress Progress to use in [0, 1] interval
   * @return Curve parameters
   */
  virtual Params params_at(double progress) const = 0;

protected:

  // Curve start point
  dvec3 _start;
  // Curve end point
  dvec3 _end;
  // Curve lentgh
  double _length{0};
};



inline Curve3d::Curve3d(const dvec3& start, const dvec3& end)
  : _start(start)
  , _end(end)
  , _length((end - start).length())
{
}



inline const dvec3& Curve3d::start() const
{
  return _start;
}



inline const dvec3& Curve3d::end() const
{
  return _end;
}



inline double Curve3d::length() const
{
  return _length;
}

} // namespace ares

#endif //__ARES_CURVE3D_H__
