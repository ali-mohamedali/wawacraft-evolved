#include "libs.hpp"
#include "logging.hpp"
#include "mesh.hpp"

graphics::mesh::mesh():
  model(math::matrix_identity()),
  vertices({}),
  indices({})
{
  glGenVertexArrays(1, &vertex_array);

  buffers_generate();
  attributes_set();
}

graphics::mesh::mesh(math::matrix<float, 4, 4> g_model, std::vector<float> g_vertices, std::vector<unsigned int> g_indices):
  model(g_model),
  vertices(g_vertices),
  indices(g_indices)
{
  buffers_generate();
  attributes_set();
}

void graphics::mesh::render()
{
  int shader;
  glGetIntegerv(GL_CURRENT_PROGRAM, &shader);
  glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, model.address());
  
  glBindVertexArray(vertex_array);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void graphics::mesh::attributes_set()
{
  glBindVertexArray(vertex_array);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void graphics::mesh::buffers_generate()
{
  glGenVertexArrays(1, &vertex_array);
  glGenBuffers(1, &vertex_buffer);
  glGenBuffers(1, &element_buffer);

  buffers_bind();
}

void graphics::mesh::model_set(math::matrix<float, 4, 4> g_model)
{
  model=g_model;
}

void graphics::mesh::set(std::vector<float> g_vertices)
{
  std::copy(g_vertices.begin(), g_vertices.end(), vertices.begin());

  buffers_bind();
}

void graphics::mesh::set(std::vector<float> g_vertices, std::vector<unsigned int> g_indices)
{
  vertices=g_vertices;
  indices=g_indices;
  
  buffers_bind();
}

void graphics::mesh::wipe()
{
  vertices.clear();
  indices.clear();

  buffers_bind();
}

math::matrix<float, 4, 4> graphics::mesh::model_get()
{
  return model;
}

std::vector<float> graphics::mesh::vertices_get()
{
  return vertices;
}

std::vector<unsigned int> graphics::mesh::indices_get()
{
  return indices;
}

void graphics::mesh::buffers_bind()
{
  logging::log pen("buffers_bind", "graphics::mesh", "From here!");
  
  glBindVertexArray(vertex_array);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}
