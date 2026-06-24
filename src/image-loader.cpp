#include "file.hpp"
#include "asset-path.hpp"
#include "logging.hpp"

file::image_loader::image_loader(std::string g_path):
  generic_loader(g_path)
{
  logging::log pen("image_loader", "file::image_loader", "New image loader for path "+path);

  stbi_set_flip_vertically_on_load(true);
  data=stbi_load(file::asset_path::qualify(path).c_str(), &width, &height, &channels, 0);
}

unsigned char* file::image_loader::file_get()
{
  return data;
}

unsigned int file::image_loader::width_get()
{
  return width;
}

unsigned int file::image_loader::height_get()
{
  return height;
}

unsigned int file::image_loader::channels_get()
{
  return channels;
}
