#ifndef BLURBS_H
#define BLURBS_H

#include "libs.hpp"
#include "common.hpp"
#include "settings.hpp"

namespace blurbs{
  void banner();
  
  void help();
  void version();

  struct help_string{
    std::string flag;
    std::string help;
  };
  
  extern const int BANNER_YES;
  extern const int BANNER_NO;

  extern const std::unordered_map<std::string, int> BANNER_TABLE;
  
  extern settings::setting<int> banner_setting;
  
  extern settings::setting<int> help_setting;
  extern settings::setting<int> version_setting;

  extern help_string help_table[];
  extern const int help_table_size;
}

#endif
