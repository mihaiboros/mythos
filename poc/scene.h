#ifndef __POC_SCENE_H__
#define __POC_SCENE_H__

#include <cstdint>
#include <hera/keymap.h>
#include <hera/light.h>
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
   * @brief Handle key events
   * @param keys Key map to use
   */
  void handle_keys(const hera::Keymap& keys);

  /**
   * @brief Draw the scene
   */
  void draw();

private:

  // model out of triangles
  hera::tModel m_tris;
  // model out of quads
  hera::qModel m_quads;
  // texture id
  uint32_t m_tex[3]{0};
  uint32_t m_idx{0};
  // has light flag
  bool m_has_light{false};
  bool m_lkey{false};
  bool m_fkey{false};
  double m_xr{0};
  double m_yr{0};
  double m_xs{0};
  double m_ys{0};
  double m_zp{-5};
  hera::Light m_light;
};

} // namespace poc

#endif //__POC_SCENE_H__
