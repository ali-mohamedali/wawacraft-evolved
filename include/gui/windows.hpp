#ifndef WINDOWS_H
#define WINDOWS_H

#include "../libs.hpp"

namespace windows{
  class window{
  public:
    typedef int resolution;
    
    window(resolution, resolution, std::string);
    ~window();

    void set_name(std::string);
    
    bool valid();
    bool should_close();

    resolution get_width();
    resolution get_height();
    
    std::string get_name();

    static const bool YES;
    static const bool NO;
    
  private:
    void poll();
    
    void initialize();
    void destroy();

    void update_name();
    void update_resolution();

    GLFWwindow* get_window_handle();
    
    bool initialized;
    
    std::string name;
    
    resolution width;
    resolution height;
    
    GLFWwindow* window_handle;
  };

  class reserve{
  public:
    static void end();
  private:
    friend class window;
    
    static bool glfw_initialized;

    static void start_glfw();
    static void end_glfw();
  };
}

#endif
