#include "gui/windows.hpp"
#include "libs.hpp"
#include "program/logging.hpp"

static bool windows::reserve::glfw_initialized=false;

static void windows::reserve::end()
{
  end_glfw();
}

static void windows::reserve::start_glfw()
{
  if(!glfw_initialized){
    glfwInit();
    glfw_initialized=true;
  }
}

static void windows::reserve::end_glfw()
{
  if(glfw_initialized){
    glfwTerminate();
    glfw_initialized=false;
  }
}
