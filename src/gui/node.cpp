#include "libs.hpp"
#include "gui/management.hpp"
#include "program/logging.hpp"

windows::node::node(const windows::window& g_window, windows::node::callback g_initializer=&default_init_callback, windows::node::callback g_updater=&default_update_callback, windows::node::callback g_death=&default_death_callback):
  updater(g_updater),
  initializer(g_initializer),
  death(g_death),
  identity(g_window),
  initialized(false)
{
  logging::log pen("node", "windows::node");
  pen.record("Initializing node with window object of window "+identity.get_name());

  pen.record("Calling node initializer callback.");
  init();
}

windows::node::~node()
{
  logging::log pen("~node", "windows::node");
  pen.record("Destroying node.");

  pen.record("Calling node death callback");
  die();
}

static void windows::node::default_init_callback(windows::window& g_window)
{
  graphics::gl_handle local_handle(&g_window);

  if(local_handle.hold()==graphics::gl_handle::SUCCESS){
    glClearColor(1, 1, 1, 1);
    
    local_handle.drop();
  }
}

static void windows::node::default_update_callback(windows::window& g_window)
{
  graphics::gl_handle local_handle(&g_window);

  if(local_handle.hold()==graphics::gl_handle::SUCCESS){
    local_handle.clear();
    glClear(GL_COLOR_BUFFER_BIT);
    
    local_handle.drop();
  }
}

static void windows::node::default_death_callback(windows::window& g_window)
{
  logging::log pen("default_death_callback", "windows::node");

  pen.record("This node has become dead.");
}

void windows::node::update()
{
  (*updater)(identity);
}

windows::node::callback windows::node::init_callback_get()
{
  return initializer;
}

windows::node::callback windows::node::update_callback_get()
{
  return updater;
}

windows::node::callback windows::node::death_callback_get()
{
  return death;
}

windows::window* windows::node::window_get()
{
  return &identity;
}

graphics::gl_handle windows::node::render_handle_get()
{
  return graphics::gl_handle(&identity);
}

void windows::node::init()
{
  if(initialized==false){
    (*initializer)(identity);
    
    initialized=true;
  }
}

void windows::node::die()
{
  if(initialized==true){
    (*death)(identity);

    initialized=false;
  }
}
