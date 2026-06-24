#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "libs.hpp"
#include "windows.hpp"
#include "common.hpp"

namespace graphics{
  namespace reserve{
    void start();
    
    void start_glad();
  }
  
  class gl_handle{
  public:
    gl_handle(windows::window*);

    void clear();
    
    bool hold();
    bool drop();
    
    static const bool SUCCESS;
    static const bool FAILURE;
  private:
    static void default_framebuffer_size_callback(GLFWwindow*, int, int);
    
    static void make_context_current(GLFWwindow*);
    static void swap_buffers(GLFWwindow*);
    static void set_framebuffer_size_callback(GLFWwindow*, GLFWframebuffersizefun);
    
    static bool handle_available();
    static bool drop_available();

    void set_initial_viewport();
    
    bool valid();
    
    static unsigned int held_handles;
    
    windows::window* window_object;
  };
}

#endif
