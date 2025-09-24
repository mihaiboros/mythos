#ifndef __HERA_ANIMATION_H__
#define __HERA_ANIMATION_H__

#include "timeline.h"

#include <ares/curve/curve.h>
#include <ares/curve/line3d.h>
#include <memory>

namespace hera
{

class Animation : public Timeline
{
public:

  /**
   * @brief Set the speed curve
   * @param speed Speed curve to set, may not be null
   */
  void set_speed(double (*speed)(double));

  /**
   * @brief Set the animation path
   * @param path Path to set
   */
  void set_path(std::unique_ptr<ares::Curve3d> path);

  /**
   * @brief Get the animation path (if any)
   * @return Animation path
   */
  const ares::Curve3d* path() const;

  /**
   * @brief Get the latest path position
   * @return Path position
   */
  const ares::dvec3& position() const;

  /**
   * @brief Get the latest path tangent
   * @return Path tangent
   */
  const ares::dvec3& tangent() const;

protected:

  /**
   * @brief Get the timeline advance step
   * @return Advance step
   */
  std::function<void(int64_t)> get_advance_step() override;

private:

  /**
   * @brief Execute advance step
   * @param usecs Elapsed microseconds since last call
   */
  void advance_step(int64_t usecs);

private:

  // latest params on the curve
  ares::Curve3d::Params _params;
  // animation speed
  double (*_speed)(double){ares::Curve::linear};
  // animation path
  std::unique_ptr<ares::Curve3d> _path{
    std::make_unique<ares::Line3d>(ares::dvec3{}, ares::dvec3{1, 1, 1})};
};



inline void Animation::set_speed(double (*speed)(double))
{
  _speed = speed;
  _params = _path->params_at(_speed(0));
}



inline void Animation::set_path(std::unique_ptr<ares::Curve3d> path)
{
  _path = std::move(path);
  _params = _path->params_at(_speed(0));
}



inline const ares::Curve3d* Animation::path() const
{
  return _path.get();
}



inline const ares::dvec3& Animation::position() const
{
  return _params.position;
}



inline const ares::dvec3& Animation::tangent() const
{
  return _params.tangent;
}



inline std::function<void(int64_t)> Animation::get_advance_step()
{
  return [this](int64_t us) { this->advance_step(us); };
}



inline void Animation::advance_step(int64_t usecs)
{
  if (0 <= total_elapsed() && total_elapsed() <= duration)
  {
    _params = _path->params_at(_speed(progression()));
  }
  else if (repeat)
  {
    handle_overshoot();
    _params = _path->params_at(_speed(progression()));
  }
  else
  {
    _params = _path->params_at(_speed(1));
    stop();
  }
}

} // namespace hera

#endif //__HERA_ANIMATION_H__
