#include "root-path.hpp"
#include "./path.h"

static std::string file::root::found="";
static std::string file::root::local="./";
static std::string file::root::installed="";

static std::vector<std::string> given;

static void file::root_path::suggest(std::string g_path)
{
  given.push_back(g_path);
}

static void file::root_path::suggest(std::vector<std::string> g_paths)
{
  given=g_paths;
}

static std::string file::root_path::get()
{
  if(found.empty()){
    found=_get_first();
  }
  
  return found;
}

static std::string file::root_path::get_first()
{
  logging::log pen("_get_first", "file::root_path", "Determining root path for this session.");

  pen.log("Getting installed path...");
  installed=ROOT_INSTALL_PATH();
  pen.log(installed);

  for(std::vector<std::string>::reverse_iterator i=given.rbegin(); i!=given.rend(); i++){
    if(_test(*i)==common::signals::YES){
      return *i;
    }
  }

  pen.error("None of your given paths work!");
  
  if(_test(local)==common::signals::YES){
    return local;
  }else if(_test(installed)==common::signals::YES){
    return installed;
  }else{
    pen.error("No path valid; no idea where to load files from!");
    return "";
  }
}

static std::string file::root_path::qualify(std::string g_path)
{
  return path_get()+g_path;
}

static bool file::root_path::test(std::string g_path)
{
  logging::log pen("test", "file::root_path", false);
  struct stat that;

  if(stat(g_path.c_str(), &that)==0 && !(that.st_mode & S_IFDIR)){
    return common::signals::YES;
  }else{
    pen.error(g_path+" does not exist!");
    return common::signals::NO;
  }
}
