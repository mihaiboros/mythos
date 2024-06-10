#include "image.h"

#include "ext/stb_image.h"

namespace
{

/**
 * @brief Release image data
 * @param data Image data to release
 */
void release_data(uint8_t* data);

} // namespace



namespace hera
{

Image::Image() = default;



Image::~Image() = default;



bool Image::load(const char* filename)
{
  int32_t channels{0};
  mdata = std::unique_ptr<uint8_t, void (*)(uint8_t*)>(
    stbi_load(filename, &width, &height, &channels, 0), release_data);
  if (channels > 0)
  {
    format = static_cast<Format>(channels - 1);
  }
  return mdata.get();
}

} // namespace hera



namespace
{

void release_data(uint8_t* data)
{
  stbi_image_free(data);
}

} // namespace
