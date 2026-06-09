#ifndef ASSET_PATH_H
#define ASSET_PATH_H

#include "libs.hpp"
#include "logging.hpp"
#include "common.hpp"
#include "settings.hpp"

namespace file{
  class asset_path{
  public:
    static void suggest(std::string);
    
    static std::string get();
    static std::string qualify(std::string);
    
    static bool test(std::string);

    static settings::arbitrator<std::string, std::string> GIVEN_ROOT;
    
  private:
    static std::string get_first();
    
    static std::string found;
    static std::string local;
    static std::string installed;
    static std::string given;
  };
}

#endif
