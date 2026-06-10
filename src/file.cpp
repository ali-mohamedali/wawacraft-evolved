#include "libs.hpp"
#include "logging.hpp"
#include "file.hpp"
#include "asset-path.hpp"

file::generic_loader::generic_loader(std::string g_path):
  path(g_path)
{
  
}

file::loader::loader(std::string g_path):
  generic_loader(g_path)
{
  logging::log log("loader", "file::loader", "File loader created for file "+path);
  
}

std::string file::loader::file_get()
{
  logging::log log("get", "file::loader", "Reading data from file "+path);
  
  file_stream.open(file::asset_path::qualify(path), std::ios::in);
  
  if(file_stream.is_open()){
    std::string accumulate="";
    std::string line;
    
    while(getline(file_stream, line)){
      accumulate+=line+"\n";
    }

    file_stream.close();

    return accumulate;
  }else{
    log.error("Unable to open file "+path);
  }

  return file::NOTHING_READ;
}

std::string file::generic_loader::path_get()
{
  return file::asset_path::qualify(path);
}
