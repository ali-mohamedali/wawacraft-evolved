#ifndef BLURBS_H
#define BLURBS_H

#include "libs.hpp"
#include "common.hpp"
#include "program/settings.hpp"

namespace blurbs{
  void banner();
  
  void help();
  void version();

  extern settings::setting<int> help_setting;
  extern settings::setting<int> version_setting;
}

#endif
