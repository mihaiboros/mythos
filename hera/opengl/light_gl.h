#ifndef __HERA_LIGHT_GL_H__
#define __HERA_LIGHT_GL_H__

#include "../light.h"
#include "heragl.h"

#include <cstdint>

namespace hera
{

enum class Light_id
{
  Light0 = GL_LIGHT0,
  Light1 = GL_LIGHT1,
  Light2 = GL_LIGHT2,
  Light3 = GL_LIGHT3,
  Light4 = GL_LIGHT4,
  Light5 = GL_LIGHT5,
  Light6 = GL_LIGHT6,
  Light7 = GL_LIGHT7
};

/**
 * @brief Setup the light
 * @param light Light to setup
 * @param id Light id to use
 */
void setup_light(const Light& light, Light_id id);

/**
 * @brief Enable light
 * @param id Light to enable
 */
void enable_light(Light_id id);

} // namespace hera



namespace hera
{

inline void setup_light(const Light& light, Light_id id)
{
  glLightfv(static_cast<GLenum>(id), GL_AMBIENT, light.ambient.rgba().data());
  glLightfv(static_cast<GLenum>(id), GL_DIFFUSE, light.diffuse.rgba().data());
  glLightfv(static_cast<GLenum>(id), GL_POSITION, light.pos.xyzw().data());
}



inline void enable_light(Light_id id)
{
  glEnable(static_cast<GLenum>(id));
}

} // namespace hera

#endif //__HERA_LIGHT_GL_H__
