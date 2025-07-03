#include "windows.hpp"
#include "libs.hpp"
#include "program/logging.hpp"

windows::window::window(resolution g_width, resolution g_height, std::string g_name):
  width(g_width),
  height(g_height),
  name(g_name),
  window_handle(NULL),
  initialized(false)
{
  logging::log pen("window", "windows::window");


  std::string init_msg="Initializing window with resolution "+std::to_string(width)+"x"+std::to_string(height)+" and name "+name;
  pen.record(init_msg);

  initialize();
}

windows::window::~window()
{
  logging::log pen("~window", "windows::window");
  pen.record("Destroying window "+name);
  
  destroy();
}

bool windows::window::valid()
{
  return (initialized && window_handle!=NULL);
}

bool windows::window::should_close()
{
  logging::log pen("should_close", "windows::window");
  
  poll();

  if(valid()){
    return glfwWindowShouldClose(window_handle);
  }else{
    pen.error("Window "+name+" lost its validity!");
    pen.record("Declaring it should close.");
  }

  return true;
}

void windows::window::poll()
{
  glfwPollEvents();
}

void windows::window::initialize()
{
  if(!initialized){
    window_handle=glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    initialized=true;
  }
}

void windows::window::destroy()
{
  glfwDestroyWindow(window_handle);
}
