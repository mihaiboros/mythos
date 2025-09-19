#ifndef __ARES_LINE_H__
#define __ARES_LINE_H__

#include "curve3d.h"

namespace ares
{

/**
 * @brief Geometric 3D line
 */
class Line : public Curve3d
{
public:

  /**
   * @brief Construct a new object
   * @param start Line start
   * @param end Line end
   */
  Line(const dvec3& start, const dvec3& end);

  /**
   * @brief Compute position at curve progress
   * @param progress Progress to use
   * @return Position at progress
   */
  dvec3 position_at(double progress) const override;

  /**
   * @brief Compute tangent at curve progress
   * @param progress Progress to use
   * @return Tangent at progress
   */
  dvec3 tangent_at(double progress) const override;

  /**
   * @brief Compute curve parameters at progress
   * @param progress Progress to use
   * @return Curve parameters
   */
  Params params_at(double progress) const override;

private:

  // Line tangent
  dvec3 _tan;
};



inline Line::Line(const dvec3& start, const dvec3& end)
  : Curve3d(start, end)
  , _tan((end - start).make_normalized())
{
}



inline dvec3 Line::position_at(double progress) const
{
  return _start + (_end - _start) * progress;
}



inline dvec3 Line::tangent_at(double progress) const
{
  return _tan;
}



inline Curve3d::Params Line::params_at(double progress) const
{
  return {.position = position_at(progress), .tangent = _tan};
}

} // namespace ares

#endif //__ARES_LINE_H__
