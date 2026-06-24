#ifndef TEXTURE_H
#define TEXTURE_H

#include "libs.hpp"
#include "file.hpp"
#include "common.hpp"

namespace graphics{
  class texture{
  public:
    texture(file::image_loader*);

    void use();
    
    unsigned int get();

    file::image_loader* image_get();
    
  protected:
    virtual void parameters_set();

    unsigned int channels();
    
    unsigned int id;
    
    file::image_loader* image;
    
  private:
    texture();
  };
}

#endif
