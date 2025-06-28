#ifndef OPTIONS_H
#define OPTIONS_H

#include "libs.hpp"
#include "blurbs.hpp"
#include "program/flags.hpp"

namespace options{
  extern flags::flag help_flag;
  extern flags::flag version_flag;

  extern flags::synonym_table flag_synonyms;

  extern flags::flag_table flag_table;

  void parse(int, char**);
}
  
#endif
