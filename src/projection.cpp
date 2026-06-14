#include "libs.hpp"
#include "projection.hpp"

const float math::pi=3.141592653589;
const float math::deg2rad=pi/180;

math::matrix<float, 4, 4> math::matrix_model(math::vector<float, 3> translation, math::quat<float> rotation, float gscale)
{
  float mscale[]=
    {gscale, 0, 0, 0,
     0, gscale, 0, 0,
     0, 0, gscale, 0,
     0, 0, 0, 1};
  math::matrix<float, 4, 4> scale(mscale);

  math::matrix<float, 4, 4> rotate=math::quat<float>::rotation_matrix(rotation);

  float mtrans[]=
    {
      1, 0, 0, translation[0],
      0, 1, 0, translation[1],
      0, 0, 1, translation[2],
      0, 0, 0, 1,
    };
  math::matrix<float, 4, 4> translate(mtrans);
  
  return translate*scale*rotate;
}

math::matrix<float, 4, 4> math::matrix_view(math::vector<float, 3> target, math::vector<float, 3> camera)
{
  math::vector<float, 3> forward=~(target-camera);
  math::vector<float, 3> up({0, 1, 0});
  math::vector<float, 3> left=up^forward;
  up=forward^left;

  float macc[]=
    {
      left[0], up[0], forward[0], 0,
      left[1], up[1], forward[1], 0,
      left[2], up[2], forward[2], 0,
      0, 0, 0, 1
    };
  math::matrix<float, 4, 4> accumulate(macc);

  float trans[]=
    {
      1, 0, 0, -camera[0],
      0, 1, 0, -camera[1],
      0, 0, 1, -camera[2],
      0, 0, 0, 1,
    };
  math::matrix<float, 4, 4> translate(trans);

  return translate*accumulate.transpose();
}

math::matrix<float, 4, 4> math::matrix_projection(float near, float far, float fov, float aspect)
{
  float angle=tan((fov*deg2rad)/2);
  
  float right=near*angle;
  float left=-right;
  float top=right/aspect;
  float bottom=-top;
  
  float mproj[]=
    {
      near/right, 0, 0, 0,
      0, near/top, 0, 0,
      0, 0, (far+near)/(far-near), -(2*far*near)/(far-near),
      0, 0, 1, 0
    };
  return matrix<float, 4, 4>(mproj);
}
