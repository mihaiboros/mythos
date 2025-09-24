#ifndef __HERA_TIMELINE_H__
#define __HERA_TIMELINE_H__

#include <functional>

namespace hera
{

class Timeline
{
public:

  /**
   * @brief Destroy the object
   */
  virtual ~Timeline();

  /**
   * @brief Start the timeline from the beginning
   */
  void start();

  /**
   * @brief Resume the timeline from the last progression
   */
  void resume();

  /**
   * @brief Stop the timeline
   */
  void stop();

  /**
   * @brief Advance timeline, called by scheduler after start/resume
   * @param usecs Elapsed microseconds since last call
   */
  void advance(int64_t usecs);

  /**
   * @brief Check if timeline is running
   * @return Result of check
   */
  bool is_running() const;

  /**
   * @brief Get total elapsed microseconds since start of loop
   * @return Total elapsed microseconds
   */
  int64_t total_elapsed() const;

  /**
   * @brief Get timeline progression (elapsed over duration)
   * @return Timeline progression
   */
  double progression() const;

public:

  // Repeat timeline after duration is reached (loop)
  bool repeat{false};
  // Progress the timeline in the forward direction
  bool forward{true};
  // Oscillate between start and end positions
  bool oscillate{false};
  // Timeline duration in microseconds (must be greater than zero)
  int64_t duration{1};

protected:

  /**
   * @brief Call when elapsed time overshoots duration and timeline is repeatable.
   * Computes direction and overshoot remainder
   */
  void handle_overshoot();

  /**
   * @brief Get timeline direction
   * @return 1 if forward, -1 if reversed
   */
  int32_t direction() const;

  /**
   * @brief Get the timeline advance step
   * @return Advance step
   */
  virtual std::function<void(int64_t)> get_advance_step() = 0;

private:

  /**
   * @brief Execute start step
   * @param usecs Elapsed microseconds since last call
   */
  void start_step(int64_t usecs);

  /**
   * @brief Execut stop step
   * @param usecs Elapsed microseconds since last call
   */
  void stop_step(int64_t usecs);

private:

  // Elapsed microseconds since start of loop
  int64_t _elapsed{0};
  // timeline step to execute
  std::function<void(int64_t)> _step;
};



inline void Timeline::stop()
{
  _step = [this](int64_t us) { this->stop_step(us); };
}



inline void Timeline::advance(int64_t usecs)
{
  _elapsed += direction() * usecs;
  _step(usecs);
}



inline void Timeline::start_step(int64_t usecs)
{
  _elapsed = 0;
  duration = duration < 1 ? 1 : duration;
  _step = get_advance_step();
  _step(0);
}



inline bool Timeline::is_running() const
{
  return _step.operator bool();
}



inline int64_t Timeline::total_elapsed() const
{
  return _elapsed;
}



inline double Timeline::progression() const
{
  return double(_elapsed) / duration;
}



inline void Timeline::handle_overshoot()
{
  forward = forward ^ oscillate;
  _elapsed = duration * (1 - forward) + (1 - 2 * oscillate) * _elapsed % duration;
}



inline int32_t Timeline::direction() const
{
  return 2 * forward - 1;
}

} // namespace hera

#endif //__HERA_TIMELINE_H__
