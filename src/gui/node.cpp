#include "libs.hpp"
#include "gui/events.hpp"
#include "gui/management.hpp"
#include "program/logging.hpp"

windows::node::node(const windows::window& g_window):
  identity(g_window),
  initialized(true)
{
  logging::log pen("node", "windows::node");
  pen.record("Initializing node with window object of window "+identity.get_name());
  
  init();
}

windows::node::~node()
{
  logging::log pen("~node", "windows::node");
  pen.record("Destroying node.");

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
  logging::log pen("window_respond", "windows::node");
  
  if(g_event.bkey==events::keyboard::KB_KEY_0){
    pen.message("0 Key was pressed!!");
  }

  std::string message;

  switch(g_event.bkey){
  case events::keyboard::KB_KEY_O:
    message+="0";
    break;
  case events::keyboard::KB_KEY_1:
    message+="1";
    break;
  case events::keyboard::KB_KEY_2:
    message+="2";
    break;
  case events::keyboard::KB_KEY_3:
    message+="3";
    break;
  case events::keyboard::KB_KEY_4:
    message+="4";
    break;
  case events::keyboard::KB_KEY_5:
    message+="5";
    break;
  case events::keyboard::KB_KEY_6:
    message+="6";
    break;
  case events::keyboard::KB_KEY_7:
    message+="7";
    break;
  case events::keyboard::KB_KEY_8:
    message+="8";
    break;
  case events::keyboard::KB_KEY_9:
    message+="9";
    break;
  default:
    message+="Unlabeled keycode";
    break;
  }
  
  switch(g_event.state){
  case events::keyboard::KB_KEY_PRESSED:
    message+=" was pressed.";
    break;
  case events::keyboard::KB_KEY_RELEASED:
    message+=" was released.";
    break;
  case events::keyboard::KB_KEY_REPEATING:
    message+=" is repeating.";
    break;
  case events::keyboard::KB_KEY_NOACTION:
  default:
    message+="; No known action was done with the key.";
    break;
  }

  pen.message(message);
}

windows::window* windows::node::window_get()
{
  return &identity;
}

graphics::gl_handle windows::node::render_handle_get()
{
  return graphics::gl_handle(&identity);
}

void windows::node::superior_set(windows::manager* g_superior)
{
  logging::log pen("superior_set", "windows::node");
  pen.record("Setting superior manager of node.");
  
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
