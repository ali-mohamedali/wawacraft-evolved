#include "gui/windows.hpp"
#include "libs.hpp"
#include "program/logging.hpp"

static const bool windows::window::YES=true;
static const bool windows::window::NO=false;

windows::window::window(windows::window::resolution g_width, windows::window::resolution g_height, std::string g_name):
  width(g_width),
  height(g_height),
  name(g_name),
  window_handle(NULL),
  initialized(false)
{
  windows::reserve::start_glfw();
  
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

void windows::window::set_name(std::string g_name)
{
  glfwSetWindowTitle(window_handle, g_name.c_str());
  update_name();
}

bool windows::window::valid()
{
  logging::log pen("valid", "windows::window");
  
  bool ret=(initialized && window_handle!=NULL) ? YES : NO;
  if(ret==NO){
    pen.error("Window lost its validity!");
    pen.record("It will be destroyed soon");
  }
  
  return ret;
}

bool windows::window::should_close()
{
  poll();

  if(valid()==YES){
    return (glfwWindowShouldClose(window_handle)) ? YES : NO;
  }

  return YES;
}

windows::window::resolution windows::window::get_width()
{
  update_resolution();
  return width;
}

windows::window::resolution windows::window::get_height()
{
  update_resolution();
  return height;
}

std::string windows::window::get_name()
{
  update_name();
  return name;
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
  initialized=false;
}

void windows::window::update_name()
{
  if(valid()==YES){
    name=glfwGetWindowTitle(window_handle);
  }
}

void windows::window::update_resolution()
{
  logging::log pen("update_resolution", "windows::window");
  
  if(valid()==YES){
    glfwGetFramebufferSize(window_handle, &width, &height);
  }
}

GLFWwindow* windows::window::get_window_handle()
{
  if(valid()==YES){
    return window_handle;
  }else{
    return NULL;
  }
}
