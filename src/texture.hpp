#ifndef TEXTURE_H
#define TEXTURE_H

#include "libs.hpp"
#include "file.hpp"
#include "common.hpp"

namespace graphics{
  class texture{
  public:
    texture(file::image_loader*);

    unsigned int get();
    
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
