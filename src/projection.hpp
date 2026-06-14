#ifndef PROJECTION_H
#define PROJECTION_H

#include "libs.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "quat.hpp"

namespace math{
  extern const float pi;
  extern const float deg2rad;
  
  matrix<float, 4, 4> matrix_model(math::vector<float, 3>, quat<float>, float);
  matrix<float, 4, 4> matrix_view(math::vector<float, 3>, math::vector<float, 3>);
  matrix<float, 4, 4> matrix_projection(float, float, float, float);
}

#endif
