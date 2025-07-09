#include "gui/windows.hpp"
#include "libs.hpp"
#include "program/logging.hpp"

bool windows::reserve::glfw_initialized=false;

void windows::reserve::start()
{
  start_glfw();
}

void windows::reserve::end()
{
  end_glfw();
}

void windows::reserve::start_glfw()
{
  if(!glfw_initialized){
    glfwInit();
    glfw_initialized=true;
  }
}

void windows::reserve::end_glfw()
{
  if(glfw_initialized){
    glfwTerminate();
    glfw_initialized=false;
  }
}

GLFWwindow* windows::reserve::get_window_handle(windows::window& g_window)
{
  return g_window.window_handle;
}
