#ifndef OPTIONS_H
#define OPTIONS_H

#include "libs.hpp"
#include "blurbs.hpp"
#include "program/flags.hpp"

namespace options{
  extern flags::flag banner_flag;
  
  extern flags::flag help_flag;
  extern flags::flag version_flag;

  extern flags::flag prefixing_flag;
  extern flags::flag logging_flag;
  extern flags::flag messages_flag;
  extern flags::flag records_flag;
  extern flags::flag errors_flag;

  extern flags::synonym_table flag_synonyms;
  extern flags::pseudo_table flag_pseudos;

  extern flags::flag_table flag_table;

  void parse(int, char**);
}
  
#endif
