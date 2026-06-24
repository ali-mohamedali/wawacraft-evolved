#ifndef FILE_H
#define FILE_H

#include "libs.hpp"
#include "logging.hpp"

namespace file{
  const std::string NOTHING_READ="";

  class generic_loader{
  public: 
    generic_loader(std::string);
    
    std::string path_get();
    
  protected:
    std::string path;
  };
  
  class loader: public generic_loader{
  public:
    loader(std::string);

    std::string file_get();
    std::string path_get();

  protected:
    std::fstream file_stream;
    
  private:
    loader();
  };

  class image_loader: public generic_loader{
  public:
    image_loader(std::string);

    unsigned char* file_get();

    unsigned int width_get();
    unsigned int height_get();
    unsigned int channels_get();
    
  protected:
    unsigned int width;
    unsigned int height;
    unsigned int channels;
    
    unsigned char* data;
  private:
    image_loader();
  };
}

#endif
