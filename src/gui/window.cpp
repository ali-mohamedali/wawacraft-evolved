#include "gui/windows.hpp"
#include "libs.hpp"
#include "program/logging.hpp"

static const bool windows::window::YES=true;
static const bool windows::window::NO=false;

windows::window::window()
{
  
}

windows::window::window(windows::window::resolution g_width, windows::window::resolution g_height, std::string g_name):
  width(g_width),
  height(g_height),
  name(g_name),
  window_handle(NULL),
  initialized(false),
  instances(new int{1})
{
  windows::reserve::start_glfw();
  
  logging::log pen("window", "windows::window");

  std::string init_msg="Initializing window with resolution "+std::to_string(width)+"x"+std::to_string(height)+" and name "+name;
  pen.record(init_msg);

  initialize();
}

windows::window::window(const windows::window& g_window):
  width(g_window.get_width()),
  height(g_window.get_height()),
  name(g_window.get_name()),
  window_handle(windows::reserve::get_window_handle(g_window)),
  initialized(true),
  instances(g_window.instances)
{
  logging::log pen("window", "windows::window");
  
  (*instances)++;
  pen.record("New instance of window "+name+" created, number of instances now "+std::to_string(*instances));
  
  update();
}

windows::window::~window()
{
  logging::log pen("~window", "windows::window");
  pen.record("Destroying window "+name);

  (*instances)--;
  if(instances==0){
    pen.record("All instances destroyed. Yes!");
    
    destroy();
  }else{
    pen.record("Number of instances of window object of window "+name+" now "+std::to_string(*instances));
  }
}

windows::window& windows::window::operator=(const windows::window& rhs)
{
  logging::log pen("operator=", "windows::window");
  pen.record("Enacting copy-by-assignment of a window object.");
  
  instances=rhs.instances;
  (*instances)++;

  pen.record("Number of instances of window object now "+std::to_string(*instances));
  
  window_handle=windows::reserve::get_window_handle(rhs);
  update();

  pen.record("Window object is now referencing window "+name);
  
  return *this;
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
  delete instances;
  
  glfwDestroyWindow(window_handle);
  initialized=false;
}

void windows::window::update()
{
  update_name();
  update_resolution();
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
