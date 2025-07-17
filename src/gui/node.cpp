#include "libs.hpp"
#include "gui/management.hpp"
#include "program/logging.hpp"

windows::node::node(const windows::window& g_window, windows::node::update_callback g_updater=&default_update_callback):
  updater(g_updater),
  identity(g_window)
{
  logging::log pen("node", "windows::node");
  pen.record("Initializing node with window object of window "+identity.get_name());
}

windows::node::~node()
{
  logging::log pen("~node", "windows::node");
  pen.record("Destroying node.");
}

static void windows::node::default_update_callback(windows::window g_window)
{
  graphics::gl_handle local_handle(&g_window);

  if(local_handle.hold()==graphics::gl_handle::SUCCESS){
    local_handle.clear();
    glClear(GL_COLOR_BUFFER_BIT);
    
    local_handle.drop();
  }
}

void windows::node::update()
{
  (*updater)(identity);
}

windows::node::update_callback windows::node::update_callback_get()
{
  return updater;
}

windows::window* windows::node::window_get()
{
  return &identity;
}

graphics::gl_handle windows::node::render_handle_get()
{
  return graphics::gl_handle(&identity);
}
