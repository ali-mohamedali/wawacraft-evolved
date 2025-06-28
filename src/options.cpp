#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "options.hpp"

flags::flag options::help_flag={false, &blurbs::help_setting};
flags::flag options::version_flag={false, &blurbs::version_setting};

flags::flag options::prefixing_flag={true, &logging::log::PREFIXING};
flags::flag options::logging_flag={true, &logging::log::LOGGING};
flags::flag options::messages_flag={true, &logging::log::MESSAGE_LOGGING};
flags::flag options::records_flag={true, &logging::log::RECORD_LOGGING};
flags::flag options::errors_flag={true, &logging::log::ERROR_LOGGING};

flags::synonym_table options::flag_synonyms=
  {
    {'v', "--version"},
    {'h', "--help"}
  };

flags::flag_table options::flag_table=
  {
    {"--help", help_flag},
    {"--version", version_flag},
    {"--logging", logging_flag},
    {"--messages", messages_flag},
    {"--record-logs", records_flag},
    {"--errors", errors_flag},
    {"--prefix", prefixing_flag}
  };

void options::parse(int argc, char** argv)
{
  flags::sieve gen_sieve(flag_synonyms, argc, argv);
  flags::parser gen_parser(flag_table);
  
  gen_parser.parse(gen_sieve.filter());
}
