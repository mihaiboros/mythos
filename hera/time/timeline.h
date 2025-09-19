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
   * @brief Start the timeline
   */
  void start();

  /**
   * @brief Stop the timeline
   */
  void stop();

  /**
   * @brief Advance timeline, called by scheduler after start
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
   * @return Total elpsed in microseconds
   */
  int64_t total_elapsed() const;

  /**
   * @brief Get timeline rate of advance (elapsed over duration)
   * @return Timeline rate of advance
   */
  double advance_rate() const;

public:

  // Repeat timeline after duration is reached (loop)
  bool repeat{false};
  // Timeline duration in microseconds
  int64_t duration{0};

protected:

  /**
   * @brief Update total elapsed time based on duration when duration is passed
   */
  void handle_overshoot();

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

  // advance step to execute
  std::function<void(int64_t)> _step;
  // Elapsed microseconds since start of loop
  int64_t _elapsed{0};
};



inline void Timeline::stop()
{
  _step = [this](int64_t us) { this->stop_step(us); };
}



inline void Timeline::advance(int64_t usecs)
{
  _elapsed += usecs;
  _step(usecs);
}



inline void Timeline::start_step(int64_t usecs)
{
  _elapsed = 0;
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



inline double Timeline::advance_rate() const
{
  return double(_elapsed) / duration;
}



inline void Timeline::handle_overshoot()
{
  _elapsed = duration > 0 ? _elapsed % duration : 0;
}

} // namespace hera

#endif //__HERA_TIMELINE_H__
