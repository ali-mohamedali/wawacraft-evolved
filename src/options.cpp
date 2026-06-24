#include "libs.hpp"
<<<<<<< HEAD
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "options.hpp"
=======
#include "flags.hpp"
#include "logging.hpp"
#include "options.hpp"
#include "asset-path.hpp"
>>>>>>> new_base

flags::flag options::banner_flag={true, &blurbs::banner_setting};

flags::flag options::help_flag={false, &blurbs::help_setting};
flags::flag options::version_flag={false, &blurbs::version_setting};

flags::flag options::prefixing_flag={true, &logging::log::PREFIXING};
flags::flag options::logging_flag={true, &logging::log::LOGGING};
flags::flag options::messages_flag={true, &logging::log::MESSAGE_LOGGING};
flags::flag options::records_flag={true, &logging::log::RECORD_LOGGING};
flags::flag options::errors_flag={true, &logging::log::ERROR_LOGGING};

<<<<<<< HEAD
=======
flags::flag options::root_flag={true, NULL, true, &file::asset_path::GIVEN_ROOT};

>>>>>>> new_base
flags::synonym_table options::flag_synonyms=
  {
    {'b', "--banner"},
    {'v', "--version"},
    {'h', "--help"},
    {'q', "--quiet"},
    {'d', "--debug"}
  };

flags::pseudo_table options::flag_pseudos=
  {
    {"--quiet", {"--logging", "nil", "--banner", "no"}},
    {"--debug", {"--logging", "t",
		 "--log-records", "t",
		 "--log-messages", "t",
		 "--log-errors", "t",
		 "--prefix", "debug"}}
  };

flags::flag_table options::flag_table=
  {
    {"--banner", banner_flag},
    {"--help", help_flag},
    {"--version", version_flag},
    {"--logging", logging_flag},
    {"--log-messages", messages_flag},
    {"--log-records", records_flag},
    {"--log-errors", errors_flag},
<<<<<<< HEAD
    {"--prefix", prefixing_flag}
=======
    {"--prefix", prefixing_flag},
    {"--root", root_flag}
>>>>>>> new_base
  };

void options::parse(int argc, char** argv)
{
  flags::sieve gen_sieve(flag_synonyms, flag_pseudos, argc, argv);
  flags::parser gen_parser(flag_table);
  
  bool call=gen_parser.parse(gen_sieve.filter());

  if(call==flags::parser::FAILURE){
    std::exit(1);
  }
}
