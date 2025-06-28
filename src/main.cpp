#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"

void OTM()
{
  std::cout << "OTM waits atop the solemn moon"
	    << "\nfor the end of all that lives."
	    << "\n\nThe lonely moon seems to"
	    << "\ntaunt you to approach your"
	    << "\ncertain demise."
	    << "\n\nHe knows where you are;"
	    << "\nYour presence has been"
	    << "\nchallenged." << std::endl;

  std::exit(0);
}

void version()
{
  std::cout << "Wawacraft:Evolved unknown indev version" << std::endl;

  std::exit(0);
}

int main(int argc, char** argv)
{
  settings::setting<int> version_setting(false, {}, &version);
  settings::setting<int> OTM_setting(false, {}, &OTM);
  
  flags::flag version_flag;
  version_flag.accepts_data=false;
  version_flag.option=&version_setting;

  flags::flag OTM_flag;
  OTM_flag.accepts_data=false;
  OTM_flag.option=&OTM_setting;
  
  flags::synonym_table synonyms=
    {
      {'v', "--version"}
    };
  
  flags::flag_table TABLE=
    {
      {"--version", version_flag},
      {"--otm", OTM_flag}
    };

  flags::sieve generic_sieve(synonyms, argc, argv);
  flags::parser generic_parser(TABLE);

  generic_parser.parse(generic_sieve.filter());

  logging::log logger("main", "global");

  logger.message("Hello World from wawacraft-evolved");
  logger.record("Recording a log");
  logger.error("Error, no error found");
  
  return 0;
}
