#include "libs.hpp"
#include "common.hpp"
#include "asset-path.hpp"

static settings::arbitrator<std::string, std::string> file::asset_path::GIVEN_ROOT(&file::asset_path::given);

static std::string file::asset_path::found="";
static std::string file::asset_path::local=".";
static std::string file::asset_path::installed="";
static std::string file::asset_path::given="";

static void file::asset_path::suggest(std::string g_path)
{
  given=g_path;
}

static std::string file::asset_path::get()
{
  logging::log pen("get", "file::asset_path", false);
  
  if(found.empty()){
    found=get_first();
    pen.record("Now loading files from "+found);
  }
  
  return found;
}

static std::string file::asset_path::get_first()
{
  logging::log pen("get_first", "file::asset_path", "Determining asset path for this session.");

  pen.record("Getting installed asset path...");
  installed=root_install_path();
  pen.record(installed);
  
  if(test(given)==common::signals::YES){
    return given;
  }else if(test(installed)==common::signals::YES){
    return installed;
  }else if(test(local)==common::signals::YES){
    return local;
  }else{
    pen.error("No path is valid; no idea where to load files from!");
    return "";
  }
}

static std::string file::asset_path::qualify(std::string g_path)
{
  return get()+"/"+g_path;
}

static bool file::asset_path::test(std::string g_path)
{
  logging::log pen("test", "file::asset_path", false);
  struct stat that;

  if(stat(g_path.c_str(), &that)==0){
    pen.record(g_path+" found!");
    return common::signals::YES;
  }else{
    pen.error(g_path+" does not exist!");
    return common::signals::NO;
  }
}
