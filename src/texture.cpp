#include "libs.hpp"
#include "texture.hpp"

graphics::texture::texture(file::image_loader* g_image):
  image(g_image)
{
  logging::log pen("texture", "graphics::texture", "New texture object created.");
  
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  parameters_set();

  if(image && image->file_get()){
    glTexImage2D(GL_TEXTURE_2D, 0, channels(), image->width_get(), image->height_get(), 0, channels(), GL_UNSIGNED_BYTE, image->file_get());
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    pen.error("Given file::image_loader pointer invalid!");
  }

  glBindTexture(GL_TEXTURE_2D, 0);
}

void graphics::texture::parameters_set()
{
  glBindTexture(GL_TEXTURE_2D, id);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

unsigned int graphics::texture::get()
{
  return id;
}

unsigned int graphics::texture::channels()
{
  return (image->channels_get()==3 ? GL_RGB :
	  (image->channels_get()==4 ? GL_RGBA : GL_RGB));
}
