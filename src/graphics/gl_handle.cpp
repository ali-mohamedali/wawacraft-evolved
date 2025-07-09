#include "libs.hpp"
#include "graphics/graphics.hpp"

static const bool graphics::gl_handle::SUCCESS=true;
static const bool graphics::gl_handle::FAILURE=false;

static unsigned int graphics::gl_handle::held_handles=0;

graphics::gl_handle::gl_handle(windows::window* g_window_object):
  window_object(g_window_object)
{
  hold();
  graphics::reserve::start();

  set_initial_viewport();
  drop();

  if(valid()==SUCCESS){
    set_framebuffer_size_callback(windows::reserve::get_window_handle(*window_object), &default_framebuffer_size_callback);
  }
}

void graphics::gl_handle::clear()
{
  if(valid()==SUCCESS){
    swap_buffers(windows::reserve::get_window_handle(*window_object));
  }
}

bool graphics::gl_handle::hold()
{
  if(valid()==SUCCESS && handle_available()==SUCCESS){
    make_context_current(windows::reserve::get_window_handle(*window_object));
    held_handles++;
    return SUCCESS;
  }

  return FAILURE;
}

bool graphics::gl_handle::drop()
{
  if(valid()==SUCCESS && drop_available()==SUCCESS){
    make_context_current(NULL);
    held_handles--;
    return SUCCESS;
  }

  return FAILURE;
}

static void graphics::gl_handle::default_framebuffer_size_callback(GLFWwindow* g_window, int g_width, int g_height)
{
  glViewport(0, 0, g_width, g_height);
}

static void graphics::gl_handle::make_context_current(GLFWwindow* g_window)
{
  glfwMakeContextCurrent(g_window);
}

static void graphics::gl_handle::swap_buffers(GLFWwindow* g_window)
{
  glfwSwapBuffers(g_window);
}

static void graphics::gl_handle::set_framebuffer_size_callback(GLFWwindow* g_window, GLFWframebuffersizefun g_callback)
{
  glfwSetFramebufferSizeCallback(g_window, g_callback);
}

static bool graphics::gl_handle::handle_available()
{
  return (held_handles<1) ? SUCCESS : FAILURE;
}

static bool graphics::gl_handle::drop_available()
{
  return (held_handles>=1) ? SUCCESS : FAILURE;
}

void graphics::gl_handle::set_initial_viewport()
{
  if(valid()==SUCCESS){
    glViewport(0, 0, window_object->get_width(), window_object->get_height());
  }
}

bool graphics::gl_handle::valid()
{
  if(window_object!=NULL){
    if(window_object->valid()==windows::window::YES){
      return SUCCESS;
    }
  }

  return FAILURE;
}
