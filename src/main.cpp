#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "options.hpp"
#include "blurbs.hpp"

int main(int argc, char** argv)
{
  options::parse(argc, argv);

  blurbs::banner();

  logging::log olog("main", "global");

  olog.message("A message!");
  olog.record("A record!");
  olog.error("Not an error!");
  
  return 0;
}
