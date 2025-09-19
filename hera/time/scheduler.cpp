#include "scheduler.h"

#include "timeline.h"

namespace hera
{

void Scheduler::run()
{
  using namespace std::chrono;
  const steady_clock::time_point now = steady_clock::now();

  const auto elapsed_us = duration_cast<microseconds>(now - _prev).count();
  for (_index = 0; _index < static_cast<int32_t>(_timelines.size()); ++_index)
  {
    _timelines[_index]->advance(elapsed_us);
  }

  _prev = now;
}

} // namespace hera
