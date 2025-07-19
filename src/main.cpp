#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "gui/windows.hpp"
#include "graphics/graphics.hpp"
#include "gui/management.hpp"
#include "options.hpp"
#include "blurbs.hpp"

void my_init(windows::window& g_window)
{
  graphics::gl_handle local_handle(&g_window);

  if(local_handle.hold()==graphics::gl_handle::SUCCESS){
    glClearColor(0.5, 0.5, 0.7, 1);
    
    local_handle.drop();
  }
}

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();
  
  windows::manager manager;

  manager.nodes_add(windows::node(windows::window(640, 480, "Instantiated Wawacraft:Evolved!"), &my_init));
  manager.nodes_add(windows::node(windows::window(400, 400, "Secondary window")));

  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();

  //pen.record("The program is ending.");
  
  return 0;
}
