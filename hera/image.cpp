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
  stbi_info(filename, &width, &height, &channels);
  const int32_t desired = 1 == channels ? 3 : 2 == channels ? 4 : channels;

  mdata = std::unique_ptr<uint8_t, void (*)(uint8_t*)>(
    stbi_load(filename, &width, &height, &channels, desired), release_data);
  has_alpha = desired > 3;

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
