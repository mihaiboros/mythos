#ifndef __HERA_IMAGE_H__
#define __HERA_IMAGE_H__

#include <cstdint>
#include <memory>

namespace hera
{

class Image
{
public:

  enum Format
  {
    Grey,
    Grey_alpha,
    Rgb,
    Rgba
  };

  /**
   * @brief Construct a new object
   */
  Image();

  /**
   * @brief Destroy the object
   */
  ~Image();

  /**
   * @brief Load an image from file
   * @param filename File name
   * @return bool Result of operation
   */
  bool load(const char* filename);

  /**
   * @brief Get texture data
   * @return const uint8_t* Image data, null if load failed
   */
  const uint8_t* data() const;

  // image width
  int32_t width{0};
  // image height
  int32_t height{0};
  // image format
  Format format{Grey};

private:

  // image data
  std::unique_ptr<uint8_t, void (*)(uint8_t*)> mdata{nullptr, nullptr};
};



inline const uint8_t* Image::data() const
{
  return mdata.get();
}

} // namespace hera

#endif //__HERA_IMAGE_H__
