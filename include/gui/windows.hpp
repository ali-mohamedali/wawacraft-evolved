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

    GLFWwindow* get_window_handle();
    
    static const bool YES;
    static const bool NO;
    
  private:
    void poll();
    
    void initialize();
    void destroy();

    void update_name();
    void update_resolution();
    
    bool initialized;
    
    std::string name;
    
    resolution width;
    resolution height;
    
    GLFWwindow* window_handle;
  };

  namespace reserve{
    void start();
    void end();

    void start_glfw();
    void end_glfw();

    extern bool glfw_initialized;
  };
}

#endif
