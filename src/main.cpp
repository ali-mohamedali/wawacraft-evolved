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
#include "projection.hpp"
#include "camera.hpp"
#include "../config.h"

float inc=0;

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

  void quickly()
  {
    const float speed=25;
    
    math::vector<float, 3> p=cam.position_get();

    events::keyboard::event w=superior_get()->node_key_get(this, events::keyboard::KB_KEY_W);
    events::keyboard::event a=superior_get()->node_key_get(this, events::keyboard::KB_KEY_A);
    events::keyboard::event s=superior_get()->node_key_get(this, events::keyboard::KB_KEY_S);
    events::keyboard::event d=superior_get()->node_key_get(this, events::keyboard::KB_KEY_D);

    events::keyboard::event up=superior_get()->node_key_get(this, events::keyboard::KB_KEY_UP);
    events::keyboard::event down=superior_get()->node_key_get(this, events::keyboard::KB_KEY_DOWN);
    events::keyboard::event left=superior_get()->node_key_get(this, events::keyboard::KB_KEY_LEFT);
    events::keyboard::event right=superior_get()->node_key_get(this, events::keyboard::KB_KEY_RIGHT);

    if(w.state==events::keyboard::KB_KEY_PRESSED){
      p=p+cam.forward_get()*(speed*glfwGetTime());
    }
    if(a.state==events::keyboard::KB_KEY_PRESSED){
      p=p-cam.left_get()*(speed*glfwGetTime());
    }
    if(s.state==events::keyboard::KB_KEY_PRESSED){
      p=p-cam.forward_get()*(speed*glfwGetTime());
    }
    if(d.state==events::keyboard::KB_KEY_PRESSED){
      p=p+cam.left_get()*(speed*glfwGetTime());
    }

    if(up.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 5*(speed*glfwGetTime()), 0);
    }
    if(down.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, -5*(speed*glfwGetTime()), 0);
    }
    if(left.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 0, 5*(speed*glfwGetTime()));
    }
    if(right.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 0, -5*(speed*glfwGetTime()));
    }

    cam.position_set(p);
  }
  
  void window_respond(events::keyboard::event given)
  {
    
  }
  
  void window_update()
  {
    logging::log pen("window_update", "test_node", false);

    inc+=25*glfwGetTime();
    
    quickly();
    glfwSetTime(0);
    
    math::matrix<float, 4, 4> model=math::matrix_model(math::vector<float, 3>({0, 0, 4}), math::quat<float>(cos(inc*math::deg2rad), 0, sin(inc*math::deg2rad), 0), 1);
    math::matrix<float, 4, 4> view=cam.view();
    math::matrix<float, 4, 4> projection=cam.projection(window_get()->get_width()/(float)window_get()->get_height());
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      local_handle.clear();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glBindTexture(GL_TEXTURE_2D, shawatex->get());
      glUseProgram(shawader->get());

      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "model"), 1, GL_FALSE, model.address());
      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "view"), 1, GL_FALSE, view.address());
      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "projection"), 1, GL_FALSE, projection.address());
      
      glBindVertexArray(shawa_vao);
      glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

      local_handle.drop();
    }
  }
  
  void init()
  {
    graphics::gl_handle local_handle=render_handle_get();
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      shawatex=new graphics::texture(&shawafile);
      vertex=new graphics::obj_shader("shaders/vertex-3d.glsl", graphics::obj_shader_type::VERTEX);
      fragment=new graphics::obj_shader("shaders/fragment-default.glsl", graphics::obj_shader_type::FRAGMENT);
      shawader=new graphics::shader(vertex, fragment);

      glClearColor(0.5, 0.5, 0.7, 1);
      glEnable(GL_DEPTH_TEST);

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
  float shawa_vert[100]=
    {
      -1, -1, -1, 0, 0,
      0, 1, 0, 0.5, 1,
      0, 1, 0, 0.5, 1,
      1, -1, -1, 1, 0,
      -1, -1, 1, 0, 0,
      0, 1, 0, 0.5, 1,
      0, 1, 0, 0.5, 1,
      1, -1, 1, 1, 0,
      -1, -1, -1, 0, 0,
      0, 1, 0, 0.5, 1,
      0, 1, 0, 0.5, 1,
      -1, -1, 1, 1, 0,
      1, -1, -1, 0, 0,
      0, 1, 0, 0.5, 1,
      0, 1, 0, 0.5, 1,
      1, -1, 1, 1, 0,
      -1, -1, 1, 0, 1,
      1, -1, 1, 1, 1,
      -1, -1, -1, 0, 0,
      1, -1, -1, 1, 0
    };

  unsigned int shawa_i[30]=
    {0, 1, 2, 0, 2, 3,
     4, 5, 6, 4, 6, 7,
     8, 9, 10, 8, 10, 11,
     12, 13, 14, 12, 14, 15,
     16, 17, 18, 19, 17, 18};
      
  graphics::gl_handle local_handle=render_handle_get();

  unsigned int shawa_vbo;
  unsigned int shawa_vao;
  unsigned int shawa_ebo;

  file::image_loader shawafile;

  graphics::camera cam;
  
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

  test_node* my_win=new test_node(windows::window(640, 480, "Wawacraft:Evolved v"+common::PROGRAM_VERSION+" [TetraSHAWAhedron]"));

  manager.nodes_add(my_win);
  
  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();
  
  return 0;
}
