#ifndef WINDOWS_H
#define WINDOWS_H

#include "../libs.hpp"
#include "../common.hpp"

namespace windows{
  class window;
  
  namespace reserve{
    void start();
    void end();

    void start_glfw();
    void end_glfw();

    GLFWwindow* get_window_handle(const windows::window&);
    
    extern bool glfw_initialized;
  };

  class window{
  public:
    typedef int resolution;

    friend GLFWwindow* windows::reserve::get_window_handle(const windows::window&);

    window();
    window(resolution, resolution, std::string);
    window(const window&); 
    ~window();
    
    window& operator=(const window&);
    
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

    void update();

    void update_name();
    void update_resolution();
    
    bool initialized;

    int* instances;
    
    std::string name;
    
    resolution width;
    resolution height;
    
    GLFWwindow* window_handle;
  };
}

#endif
