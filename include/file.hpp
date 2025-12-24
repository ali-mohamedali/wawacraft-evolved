#ifndef FILE_H
#define FILE_H

#include "libs.hpp"
#include "program/logging.hpp"

namespace file{
  class loader{
  public:
    loader(std::string);

    std::string get();
    
  private:
    const std::string path;

    std::ifstream file_stream;
  };
}
