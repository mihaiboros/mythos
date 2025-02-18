#ifndef __POC_SCENE_H__
#define __POC_SCENE_H__

#include <cstdint>
#include <hera/keymap.h>
#include <hera/light.h>
#include <hera/model.h>
#include <memory>

namespace poc
{

class Scene
{
public:

  struct Renderer;

  /**
   * @brief Construct a new object
   */
  Scene();

  /**
   * @brief Destroy the object
   */
  ~Scene();

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
  void handle_keys(hera::Keymap& keys);

  /**
   * @brief Draw the scene
   */
  void draw();

private:

  // model out of triangles
  hera::Model m_tris;
  // model out of quads
  hera::Model m_quads;
  // has light flag
  bool m_has_light{false};
  bool m_lkey{false};
  bool m_bkey{false};
  bool m_has_blend{false};
  double m_xr{0};
  double m_yr{0};
  double m_xs{0};
  double m_ys{0};
  double m_zp{-5};
  hera::Light m_light;
  // Renderer setup
  std::unique_ptr<Renderer> m_renderer;
};

} // namespace poc

#endif //__POC_SCENE_H__
