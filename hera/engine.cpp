#include "engine.h"

namespace
{

// default event handlers
void default_handle_key(uint8_t, bool) {};
void default_handle_generic(int32_t, int32_t) {};

} // namespace

namespace hera
{

Engine::Engine()
  : on_key{default_handle_key}
  , on_resize{default_handle_generic}
  , on_mouse_move{default_handle_generic}
{
}

} // namespace hera

namespace
{

} // namespace
