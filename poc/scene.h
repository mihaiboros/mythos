#ifndef __POC_SCENE_H__
#define __POC_SCENE_H__

#include <cstdint>

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
   * @brief Draw the scene
   */
  void draw();

private:
};

} // namespace poc

#endif //__POC_SCENE_H__
