#include "libs.hpp"
#include "camera.hpp"

graphics::camera::camera():
  fov(50),
  near(1),
  far(100),
  roll(0),
  pitch(0),
  yaw(0),
  orientation(cos(0), 0, 0, sin(0)),
  position({0, 0, 0})
{
  
}

graphics::camera::camera(math::vector<float, 3> g_position, math::quat<float> g_orientation, float g_fov, float g_near, float g_far):
  fov(g_fov),
  near(g_near),
  far(g_far),
  position(g_position),
  orientation(g_orientation)
{
  
}

void graphics::camera::orientation_set(math::vector<float, 3> g_orientation)
{
  orientation=math::quat<float>(0, g_orientation[0], g_orientation[1], g_orientation[2]);
  view_calculate();
}

void graphics::camera::position_set(math::vector<float, 3> g_position)
{
  position=g_position;
  view_calculate();
}

void graphics::camera::rotate(float g_roll, float g_pitch, float g_yaw)
{
  roll+=g_roll;
  pitch+=g_pitch;
  yaw+=(pitch>90 ? -g_yaw : g_yaw);

  if(roll>=360){roll-=360;}
  if(pitch>=360){pitch-=360;}
  if(yaw>=360){yaw-=360;}
  
  math::quat<float> qroll(cos(roll*math::deg2rad/2), 0, 0, sin(roll*math::deg2rad/2));
  math::quat<float> qpitch(cos(pitch*math::deg2rad/2), sin(pitch*math::deg2rad/2), 0, 0);
  math::quat<float> qyaw(cos(yaw*math::deg2rad/2), 0, sin(yaw*math::deg2rad/2), 0);

  math::quat<float> comp=qpitch*qyaw;

  orientation=comp;
  view_calculate();
}

void graphics::camera::fov_set(float g_fov)
{
  fov=g_fov;
}

void graphics::camera::near_set(float g_near)
{
  near=g_near;
}

void graphics::camera::far_set(float g_far)
{
  far=g_far;
}

math::matrix<float, 4, 4>* graphics::camera::view_get()
{
  return &view;
}

void graphics::camera::view_calculate()
{
  
  float mtrans[]=
    {
      1, 0, 0, -position[0],
      0, 1, 0, -position[1],
      0, 0, 1, -position[2],
      0, 0, 0, 1
    };
  view=math::quat<float>::rotation_matrix(orientation)*math::matrix<float, 4, 4>(mtrans);
}

math::matrix<float, 4, 4>* graphics::camera::projection_get(float aspect)
{
  projection=math::matrix_projection(near, far, fov, aspect);

  return &projection;
}

math::vector<float, 3> graphics::camera::position_get()
{
  return position;
}

math::vector<float, 3> graphics::camera::forward_get()
{
  math::quat<float> forward(0, 0, 0, 1);
  math::quat<float> r=(orientation.inverse()*forward*(~orientation.inverse()));
  
  return (math::vector<float, 3>({r.i_get(), r.j_get(), r.k_get()}));
}

math::vector<float, 3> graphics::camera::left_get()
{
  math::quat<float> left(0, 1, 0, 0);
  math::quat<float> r=(orientation.inverse()*left*(~orientation.inverse()));
  return (math::vector<float, 3>({r.i_get(), r.j_get(), r.k_get()}));
}

math::vector<float, 3> graphics::camera::up_get()
{
  return math::vector<float, 3>({0, 1, 0});
}

float graphics::camera::fov_get()
{
  return fov;
}

float graphics::camera::near_get()
{
  return near;
}

float graphics::camera::far_get()
{
  return far;
}
