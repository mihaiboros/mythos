#include "timeline.h"

#include "../engine.h"

namespace hera
{

Timeline::~Timeline()
{
  if (_step)
  {
    engine.scheduler.remove(this);
  }
}



void Timeline::start()
{
  engine.scheduler.add(this);
  _step = [this](int64_t us) { this->start_step(us); };
}



void Timeline::stop_step(int64_t usecs)
{
  engine.scheduler.remove(this);
  _step = {};
}

} // namespace hera
