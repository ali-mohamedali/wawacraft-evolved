#include "libs.hpp"
#include "program/flags.hpp"
#include "program/logging.hpp"
#include "gui/windows.hpp"
#include "graphics/graphics.hpp"
#include "gui/management.hpp"
#include "options.hpp"
#include "blurbs.hpp"

class test_node: public windows::node{
public:
  test_node(const windows::window& g_window):
    node(g_window)
  {
    init();
  }

  void window_update()
  {
    logging::log pen("window_update", "test_node", false);
    
    graphics::gl_handle local_handle=render_handle_get();

    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      local_handle.clear();
      glClear(GL_COLOR_BUFFER_BIT);
      
      local_handle.drop();
    }

    if(superior->node_key_get(this, events::keyboard::KB_KEY_W).state==events::keyboard::KB_KEY_PRESSED){
      pen.message("W KEY IS DOWN!!");
    }
  }
  
  void init()
  {
    graphics::gl_handle local_handle=render_handle_get();

    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      glClearColor(0.5, 0.5, 0.7, 1);
      
      local_handle.drop();
    }
  }
};

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();

  windows::manager manager;

  test_node* my_win=new test_node(windows::window(640, 480, "Wawacraft:Evolved!"));
  windows::node* secondary_win=new windows::node(windows::window(400, 400, "Secondary Window"));

  manager.nodes_add(my_win);
  manager.nodes_add(secondary_win);
  
  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();
  
  return 0;
}
