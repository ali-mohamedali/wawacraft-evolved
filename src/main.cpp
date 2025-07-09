#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "gui/windows.hpp"
#include "graphics/graphics.hpp"
#include "options.hpp"
#include "blurbs.hpp"

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();
  
  windows::window testwin(800, 600, "Wawacraft:Evolved test window!");
  graphics::gl_handle testgl(&testwin);
  
  logging::log pen("main", "");

  testgl.hold();
  
  glClearColor(0.5, 0.5, 0.7, 1);
  while(!testwin.should_close()){
    glClear(GL_COLOR_BUFFER_BIT);
    testgl.clear();
  }
  testgl.drop();
  
  windows::reserve::end();
  
  return 0;
}
