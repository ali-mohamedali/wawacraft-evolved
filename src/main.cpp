#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "gui/windows.hpp"
#include "graphics/graphics.hpp"
#include "gui/management.hpp"
#include "options.hpp"
#include "blurbs.hpp"

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();
  
  windows::window* testwin=new windows::window(200, 200, "Wawacraft:Evolved test window!");
  graphics::gl_handle testgl(testwin);

  windows::window* testwin2=new windows::window(200, 200, "Wawacraft:Evolved secondary window!");
  graphics::gl_handle win2gl(testwin2);
  
  logging::log pen("main", "");

  if(testgl.hold()==graphics::gl_handle::SUCCESS){
    glClearColor(0.5, 0.5, 0.7, 1);
    
    testgl.drop();
  }
  
  if(win2gl.hold()==graphics::gl_handle::SUCCESS){
    glClearColor(0.8, 0.5, 0.2, 1);
    
    win2gl.drop();
  }
  
  pen.record("Making node only");
  windows::node* testnode=new windows::node(*testwin);
  windows::node* node2=new windows::node(*testwin2);

  delete testwin;
  delete testwin2;
  
  windows::manager manager;
  
  manager.nodes_add(testnode);
  manager.nodes_add(node2);
  
  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();

  pen.record("The program is ending.");
  
  return 0;
}
