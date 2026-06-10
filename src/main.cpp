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
#include "asset-path.hpp"
#include "texture.hpp"
#include "../config.h"

class test_node: public windows::node{
public:
  test_node(const windows::window& g_window):
    node(g_window),
    shawafile("textures/wawa.png")
  {
    init();
  }

  ~test_node()
  {
    delete vertex;
    delete fragment;
    delete shawader;
    delete shawatex;
  }
  
  void window_update()
  {
    logging::log pen("window_update", "test_node", false);
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      local_handle.clear();
      glClear(GL_COLOR_BUFFER_BIT);

      glBindTexture(GL_TEXTURE_2D, shawatex->get());
      glUseProgram(shawader->get());
      glBindVertexArray(shawa_vao);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      local_handle.drop();
    }
  }
  
  void init()
  {
    graphics::gl_handle local_handle=render_handle_get();
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      shawatex=new graphics::texture(&shawafile);
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
      
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
      glEnableVertexAttribArray(1);
      glBindVertexArray(0);
      
      local_handle.drop();
    }
  }
private:
  float shawa_vert[25]=
    {
      -1, -1, 0, 0, 0,
      -1, 1, 0, 0, 1,
      1, 1, 0, 1, 1,
      1, -1, 0, 1, 0,
      0, 1, 0, 0.5, 1
    };

  unsigned int shawa_i[6]=
    {0, 1, 2, 0, 2, 3};
      
  graphics::gl_handle local_handle=render_handle_get();

  unsigned int shawa_vbo;
  unsigned int shawa_vao;
  unsigned int shawa_ebo;

  file::image_loader shawafile;
  
  graphics::obj_shader* vertex;
  graphics::obj_shader* fragment;
  graphics::shader* shawader;
  graphics::texture* shawatex;
};

int main(int argc, char** argv)
{
  options::parse(argc, argv);
  blurbs::banner();

  windows::manager manager;

  test_node* my_win=new test_node(windows::window(640, 480, "Wawacraft:Evolved!"));

  manager.nodes_add(my_win);
  
  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();
  
  return 0;
}
