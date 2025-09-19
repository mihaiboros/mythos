#ifndef __HERA_SCHEDULER_H__
#define __HERA_SCHEDULER_H__

#include <chrono>
#include <vector>

namespace hera
{

// forward declarations
class Timeline;

class Scheduler
{
public:

  /**
   * @brief Run the scheduler
   */
  void run();

  /**
   * @brief Schedule timeline to run
   * @param tl Timeline to schedule, may not be null, does not take ownerhip
   */
  void add(Timeline* tl);

  /**
   * @brief Remove timeline from scheduler
   * @param tl Timeline to remove, may not be null, does not take ownerhip
   */
  void remove(Timeline* tl);

private:

  // current running time line index
  int32_t _index{0};

  // previous time point
  std::chrono::steady_clock::time_point _prev{std::chrono::steady_clock::now()};

  // timelines registered for running
  std::vector<Timeline*> _timelines;
};



inline void Scheduler::add(Timeline* tl)
{
  if (const auto it = std::lower_bound(_timelines.begin(), _timelines.end(), tl);
      it == _timelines.end() || *it != tl)
  {
    _timelines.insert(it, tl);
  }
}



inline void Scheduler::remove(Timeline* tl)
{
  if (!_timelines.empty())
  {
    const auto it = _index < static_cast<int64_t>(_timelines.size()) && _timelines[_index] == tl
                    ? _timelines.begin() + _index
                    : std::lower_bound(_timelines.begin(), _timelines.end(), tl);
    if (it - _timelines.begin() <= _index && _index > 0)
    {
      --_index;
    }
    _timelines.erase(it);
  }
}

} // namespace hera

#endif //__HERA_SCHEDULER_H__
