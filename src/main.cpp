#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "options.hpp"
#include "blurbs.hpp"

int main(int argc, char** argv)
{
  options::parse(argc, argv);

  blurbs::banner();
  
  logging::log logger;

  logger.message("Hello World from wawacraft-evolved");
  logger.record("Recording a log");
  logger.error("Error, no error found");
  
  return 0;
}
