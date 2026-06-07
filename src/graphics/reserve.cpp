#include "libs.hpp"
#include "graphics/graphics.hpp"
#include "program/logging.hpp"

void graphics::reserve::start()
{
  windows::reserve::start();
  start_glad();
}

void graphics::reserve::start_glad()
{
  logging::log pen("start_glad", "graphics::reserve");
  
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    pen.error("Failed to initialize GLAD");
    pen.record("OpenGL functions will not work from here on!");
  }
}
