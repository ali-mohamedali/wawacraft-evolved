#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "gui/windows.hpp"
#include "options.hpp"
#include "blurbs.hpp"

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();
  
  windows::window testwin(800, 600, "Wawacraft:Evolved test window!");

  logging::log pen("main", "");

  pen.message("Initial name of window is "+testwin.get_name());

  testwin.set_name("TATER SALAD!");
  
  pen.message("Name changed to "+testwin.get_name());
  
  while(!testwin.should_close()){
    //pen.record("Name of window is "+testwin.get_name());
    pen.record("Resolution: "+std::to_string(testwin.get_width())+"x"+std::to_string(testwin.get_height()));
  }
  
  windows::reserve::end();
  
  return 0;
}
