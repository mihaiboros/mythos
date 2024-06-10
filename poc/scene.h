#ifndef __POC_SCENE_H__
#define __POC_SCENE_H__

#include <cstdint>
#include <hera/model.h>

namespace poc
{

class Scene
{
public:

  /**
   * @brief Initialize the scene
   * @param width Scene width
   * @param height Scene height
   */
  void init(int32_t width, int32_t height);

  /**
   * @brief Resize the scene
   * @param width Scene width
   * @param height Scene height
   */
  void resize(int32_t width, int32_t height);

  /**
   * @brief Load the scene
   */
  void load();

  /**
   * @brief Draw the scene
   */
  void draw();

private:

  // model out of triangles
  hera::Model mtris;
  // model out of quads
  hera::Model mquads;
  // texture id
  uint32_t mtex_id{0};
};

} // namespace poc

#endif //__POC_SCENE_H__
