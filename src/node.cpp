#include "libs.hpp"
#include "events.hpp"
#include "management.hpp"
#include "logging.hpp"

windows::node::node(const windows::window& g_window):
  identity(g_window),
  initialized(true)
{
  logging::log pen("node", "windows::node", "Initializing node with window object of window "+identity.get_name());
  
  init();
}

windows::node::~node()
{
  logging::log pen("~node", "windows::node", "Destroying node.");
  initialized=false;
}

void windows::node::window_update()
{
  graphics::gl_handle local_handle=render_handle_get();

  if(local_handle.hold()==graphics::gl_handle::SUCCESS){
    local_handle.clear();
    glClear(GL_COLOR_BUFFER_BIT);
    
    local_handle.drop();
  }
}

void windows::node::window_respond(events::keyboard::event g_event)
{
  
}

windows::window* windows::node::window_get()
{
  return &identity;
}

windows::manager* windows::node::superior_get()
{
  return superior;
}

graphics::gl_handle windows::node::render_handle_get()
{
  return graphics::gl_handle(&identity);
}

void windows::node::superior_set(windows::manager* g_superior)
{
  logging::log pen("superior_set", "windows::node", "Setting superior manager of node.");
  
  superior=g_superior;

  if(superior==NULL){
    pen.error("Invalid pointer given for node superior.");
  }
}

void windows::node::init()
{
  graphics::gl_handle local_handle=render_handle_get();

  if(local_handle.hold()==graphics::gl_handle::SUCCESS){
    glClearColor(1, 1, 1, 1);
    
    local_handle.drop();
  }
}
