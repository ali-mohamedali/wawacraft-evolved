#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "options.hpp"
#include "blurbs.hpp"

int main(int argc, char** argv)
{
  options::parse(argc, argv);

  blurbs::banner();
  
  return 0;
}
