#include "libs.hpp"
#include "mesh.hpp"

graphics::textured_mesh::textured_mesh()
{
  attributes_set();
}

graphics::textured_mesh::textured_mesh(math::matrix<float, 4, 4> g_model, std::vector<float> g_vertices, std::vector<unsigned int> g_indices):
  mesh(g_model, g_vertices, g_indices)
{
  attributes_set();
}

void graphics::textured_mesh::render(graphics::texture* g_texture)
{
  int shader;
  glGetIntegerv(GL_CURRENT_PROGRAM, &shader);
  if(g_texture){g_texture->use();}
  glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, model.address());
  
  glBindVertexArray(vertex_array);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void graphics::textured_mesh::attributes_set()
{
  glBindVertexArray(vertex_array);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}
