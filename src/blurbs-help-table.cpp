#include "libs.hpp"
#include "blurbs.hpp"

const int blurbs::help_table_size=10;

blurbs::help_string blurbs::help_table[blurbs::help_table_size]=
  {
    {"--help,-h",
     "Display this help text."},
    {"--banner,-b [yes,no]",
     "Show program banner with an argument."},
    {"--version,-b",
     "Show the program version and exit."},
    {"--logging [t,nil]",
     "Specify presence of all output through stdout and stderr."},
    {"--log-messages [t,nil]",
     "Specify presence of dialogs through stdout, stderr."},
    {"--log-records [t,nil]",
     "Specify presence of diagnostics through stdout, stderr."},
    {"--log-errors [t,nil]",
     "Specify presence of error messages through stdout, stderr."},
    {"--prefix [nil,regular,debug,t]",
     "Specify detail of message prefixing."},
    {"--quiet,-q",
     "Show no output through stdout, stderr at all.  Dangerous!"},
    {"--debug,-d",
     "Show all messages, errors, diagnostics, using maximal prefixing."}
  };
