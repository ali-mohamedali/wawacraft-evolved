#ifndef FILE_H
#define FILE_H

#include "libs.hpp"
#include "logging.hpp"

namespace file{
  const std::string NOTHING_READ="";
  
  class loader{
  public:
    loader(std::string);

    std::string file_get();
    std::string path_get();
    
  private:
    loader();
    
    const std::string path;

    std::fstream file_stream;
  };
}

#endif
