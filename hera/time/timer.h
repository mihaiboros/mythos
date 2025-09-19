#ifndef __HERA_TIMER_H__
#define __HERA_TIMER_H__

#include "timeline.h"

namespace hera
{

class Timer : public Timeline
{
public:

  // Called when the timer expires
  std::function<void(Timer&)> expired;

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
};



inline std::function<void(int64_t)> Timer::get_advance_step()
{
  return [this](int64_t us) { this->advance_step(us); };
}



inline void Timer::advance_step(int64_t usecs)
{
  if (total_elapsed() >= duration)
  {
    if (expired)
    {
      expired(*this);
    }
    if (repeat)
    {
      handle_overshoot();
    }
    else
    {
      stop();
    }
  }
}

} // namespace hera

#endif //__HERA_TIMER_H__
