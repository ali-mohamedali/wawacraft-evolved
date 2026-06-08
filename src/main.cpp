#include "libs.hpp"
#include "flags.hpp"
#include "logging.hpp"
#include "windows.hpp"
#include "graphics.hpp"
#include "management.hpp"
#include "options.hpp"
#include "blurbs.hpp"
#include "file.hpp"
#include "shader.hpp"
#include "../config.h"

class test_node: public windows::node{
public:
  test_node(const windows::window& g_window):
    node(g_window)
  {
    init();
  }

  ~test_node()
  {
    delete vertex;
    delete fragment;
    delete shawader;
  }
  
  void window_update()
  {
    logging::log pen("window_update", "test_node", false);
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      local_handle.clear();
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shawader->get());
      glBindVertexArray(shawa_vao);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

      local_handle.drop();
    }
  }
  
  void init()
  {
    graphics::gl_handle local_handle=render_handle_get();
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      vertex=new graphics::obj_shader("shaders/vertex-default.glsl", graphics::obj_shader_type::VERTEX);
      fragment=new graphics::obj_shader("shaders/fragment-default.glsl", graphics::obj_shader_type::FRAGMENT);
      shawader=new graphics::shader(vertex, fragment);

      glClearColor(0.5, 0.5, 0.7, 1);

      glGenVertexArrays(1, &shawa_vao);
      glBindVertexArray(shawa_vao);

      glGenBuffers(1, &shawa_vbo);
      glBindBuffer(GL_ARRAY_BUFFER, shawa_vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(shawa_vert), shawa_vert, GL_STATIC_DRAW);

      glGenBuffers(1, &shawa_ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shawa_ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shawa_i), shawa_i, GL_STATIC_DRAW);
      
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);
      glBindVertexArray(0);
      
      local_handle.drop();
    }
  }
private:
  float shawa_vert[9]=
    {
      -0.5, -0.5, 0,
      0.5, -0.5, 0,
      0, 0.5, 0
    };

  unsigned int shawa_i[3]=
    {0, 1, 2};
      
  graphics::gl_handle local_handle=render_handle_get();

  unsigned int shawa_vbo;
  unsigned int shawa_vao;
  unsigned int shawa_ebo;

  graphics::obj_shader* vertex;
  graphics::obj_shader* fragment;
  graphics::shader* shawader;
};

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();

  windows::manager manager;

  test_node* my_win=new test_node(windows::window(640, 480, "Wawacraft:Evolved!"));
  test_node* copy=new test_node(windows::window(400, 400, "copy of first window"));

  manager.nodes_add(my_win);
  manager.nodes_add(copy);
  
  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();
  
  return 0;
}
