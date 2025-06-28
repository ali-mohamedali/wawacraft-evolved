#include "libs.hpp"
#include "program/flags.hpp"
#include "options.hpp"

flags::flag options::help_flag={false, &blurbs::help_setting};
flags::flag options::version_flag={false, &blurbs::version_setting};

flags::synonym_table options::flag_synonyms=
  {
    {'v', "--version"},
    {'h', "--help"}
  };

flags::flag_table options::flag_table=
  {
    {"--help", help_flag},
    {"--version", version_flag}
  };

void options::parse(int argc, char** argv)
{
  flags::sieve gen_sieve(flag_synonyms, argc, argv);
  flags::parser gen_parser(flag_table);
  
  gen_parser.parse(gen_sieve.filter());
}
