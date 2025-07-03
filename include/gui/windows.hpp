#ifndef WINDOWS_H
#define WINDOWS_H

#include "../libs.hpp"

namespace windows{
  typedef int resolution;
  
  class window{
  public:
    window(resolution, resolution, std::string);
    ~window();

    bool valid();
    bool should_close();
    
  private:
    void poll();
    
    void initialize();
    void destroy();
    
    bool initialized;
    
    std::string name;
    
    resolution width;
    resolution height;
    
    GLFWwindow* window_handle;
  };
}

#endif
