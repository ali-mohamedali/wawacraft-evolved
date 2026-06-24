#ifndef COMMON_H
#define COMMON_H

#include "libs.hpp"
#include "config.h"

namespace common{
  static const std::string PROGRAM_NAME=PACKAGE_NAME;
  static const std::string PROGRAM_NAME_FORMAL="Wawacraft:Evolved";
  static const std::string PROGRAM_VERSION=PACKAGE_VERSION;
  
  namespace signals{
    static const bool YES=true;
    static const bool NO=false;
    
    static const bool SUCCESS=true;
    static const bool FAILURE=false;
  }

  namespace values{
    static const bool MUTEX_HELD=true;
    static const bool MUTEX_DROPPED=false;
  }
}

#endif
