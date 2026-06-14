#include "libs.hpp"
#include "time.hpp"

void wtime::reset()
{
  glfwSetTime(0);
}

float wtime::now()
{
  return glfwGetTime();
}
