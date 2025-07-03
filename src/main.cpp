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

  glfwInit();
  
  windows::window testwin(800, 600, "Wawacraft:Evolved test window!");

  while(!testwin.should_close()){
    
  }
  
  return 0;
}
