#ifndef MESH_H
#define MESH_H

#include "libs.hpp"
#include "projection.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "file.hpp"

namespace graphics{
  class mesh{
  public:
    mesh();
    mesh(math::matrix<float, 4, 4>, std::vector<float>, std::vector<unsigned int>);

    virtual void render();
    
    void model_set(math::matrix<float, 4, 4>);

    void set(std::vector<float>);
    void set(std::vector<float>, std::vector<unsigned int>);

    void wipe();

    math::matrix<float, 4, 4> model_get();

    std::vector<float> vertices_get();
    std::vector<unsigned int> indices_get();
    
  protected:
    virtual void attributes_set();
    
    void buffers_generate();
    void buffers_bind();
    
    math::matrix<float, 4, 4> model;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int vertex_array;
    unsigned int vertex_buffer;
    unsigned int element_buffer;
  };

  class textured_mesh: public mesh{
  public:
    textured_mesh();
    textured_mesh(math::matrix<float, 4, 4>, std::vector<float>, std::vector<unsigned int>);

    void render(graphics::texture*);
    
  protected:
    void attributes_set();
    
  };
}

#endif
