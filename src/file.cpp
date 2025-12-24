#include "libs.hpp"
#include "program/logging.hpp"
#include "file.hpp"

file::loader::loader(std::string g_path):
  path(g_path),
  file_stream(path)
{
  logging::log log("loader", "file::loader");

  
}

std::string file::loader::get()
{
  if(file_stream.is_open()){
    
  }
}
