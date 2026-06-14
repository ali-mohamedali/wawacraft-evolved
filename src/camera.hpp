#ifndef CAMERA_H
#define CAMERA_H

#include "libs.hpp"
#include "vector.hpp"
#include "quat.hpp"
#include "projection.hpp"

namespace graphics{
  class camera{
  public:
    camera();
    camera(math::vector<float, 3>, math::vector<float, 3>, float, float, float);

    void orientation_set(math::vector<float, 3>);
    void position_set(math::vector<float, 3>);

    void rotate(float, float, float);
    
    void fov_set(float);

    void near_set(float);
    void far_set(float);

    math::matrix<float, 4, 4> view();
    math::matrix<float, 4, 4> projection(float);
    
    math::vector<float, 3> position_get();
    math::vector<float, 3> forward_get();
    math::vector<float, 3> up_get();
    math::vector<float, 3> left_get();
    
    float fov_get();

    float near_get();
    float far_get();
    
  private:
    math::quat<float> orientation;
    
    math::vector<float, 3> position;

    float roll;
    float pitch;
    float yaw;
    
    float fov;
    
    float near;
    float far;
  };
}

#endif
