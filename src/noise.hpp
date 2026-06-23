#ifndef NOISE_H
#define NOISE_H

#include "libs.hpp"
#include "vector.hpp"
#include "projection.hpp"
#include "time.hpp"

namespace math{
  float interpolate(float, float, float, float);
  
  class noise_2d{
  public:
    noise_2d(unsigned int);

    float sample(float, float);
    
  private:
    noise_2d();

    unsigned int coord(unsigned int, unsigned int);
    
    unsigned int size;
    
    std::vector<unsigned int> lattice;
  };
}

#endif
