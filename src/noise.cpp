#include "libs.hpp"
#include "noise.hpp"

float math::interpolate(float y1, float y2, float dx, float x)
{
  return y1+(y2-y1)*x/dx;
}

math::noise_2d::noise_2d(unsigned int g_size):
  size(g_size)
{
  lattice.resize(size*size);
  
  srand(wtime::now());
  for(int i=0; i<size*size; i++){
    lattice[i]=(((float)(rand()%360))*math::deg2rad);
  }
}

unsigned int math::noise_2d::coord(unsigned int i, unsigned int j)
{
  return (j*size+i);
}

float math::noise_2d::sample(float i, float j)
{
  float ic=std::floor(i);
  float jc=std::floor(j);

  unsigned int line=size;
  
  math::vector<float, 2> ai({cos(lattice[coord(ic, jc)]), sin(lattice[coord(ic, jc)])});
  math::vector<float, 2> aii({cos(lattice[coord(ic+1, jc)]), sin(lattice[coord(ic+1, jc)])});
  math::vector<float, 2> aiii({cos(lattice[coord(ic, jc+1)]), sin(lattice[coord(ic, jc+1)])});
  math::vector<float, 2> aiv({cos(lattice[coord(ic+1, jc+1)]), sin(lattice[coord(ic+1, jc+1)])});

  math::vector<float, 2> di({i-ic, j-jc});
  math::vector<float, 2> dii({i-(ic+1), j-jc});
  math::vector<float, 2> diii({i-ic, j-(jc+1)});
  math::vector<float, 2> div({i-(ic+1), j-(jc+1)});

  float pi=di*ai;
  float pii=dii*aii;
  float piii=diii*aiii;
  float piv=div*aiv;
  
  float finale=interpolate(interpolate(pi, pii, 1, i-ic), interpolate(piii, piv, 1, i-ic), 1, j-jc);

  return finale;
}
