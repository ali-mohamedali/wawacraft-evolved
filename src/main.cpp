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
#include "time.hpp"
#include "mesh.hpp"
#include "../config.h"

float inc=0;

class test_node: public windows::node{
public:
  test_node(const windows::window& g_window):
    node(g_window),
    shawafile("textures/wawa.png"),
    cam(math::vector<float, 3>({0, 0, 0}), math::quat<float>(cos(0), 0, 0, sin(0)), 50, 1, 800)
  {
    init();
  }

  ~test_node()
  {
    delete vertex;
    delete fragment;
    delete shawader;
    delete shawa;
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
      p=p+cam.forward_get()*(speed*wtime::now());
    }
    if(a.state==events::keyboard::KB_KEY_PRESSED){
      p=p-cam.left_get()*(speed*wtime::now());
    }
    if(s.state==events::keyboard::KB_KEY_PRESSED){
      p=p-cam.forward_get()*(speed*wtime::now());
    }
    if(d.state==events::keyboard::KB_KEY_PRESSED){
      p=p+cam.left_get()*(speed*wtime::now());
    }

    if(up.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 5*(speed*wtime::now()), 0);
    }
    if(down.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, -5*(speed*wtime::now()), 0);
    }
    if(left.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 0, 5*(speed*wtime::now()));
    }
    if(right.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 0, -5*(speed*wtime::now()));
    }

    cam.position_set(p);
  }
  
  void window_respond(events::keyboard::event given)
  {
    quickly();
  }

  void duplicate(math::vector<float, 3> offset, unsigned int depth)
  {
    math::vector<float, 3> left({2*depth, 2*depth, 2});
    math::vector<float, 3> right({-2*(signed int)depth, 2*depth, 2});
    
    math::quat<float> rotation(cos(inc*math::deg2rad), 0, sin(inc*math::deg2rad), 0);
    
    shawa->model_set(math::matrix_model(offset, rotation, 1));
    shawa->render();

    if(depth!=0){
      duplicate(offset+left, depth-1);
      duplicate(offset+right, depth-1);
    }
  }
  
  void window_update()
  {
    logging::log pen("window_update", "test_node", false);

    inc+=25*wtime::now();

    quickly();
    wtime::reset();

    math::vector<float, 3> offset({0, 0, 4});
    math::vector<float, 3> left({2, 2, 0});
    math::vector<float, 3> right({-2, 2, 0});
    
    math::quat<float> rotation(cos(inc*math::deg2rad), 0, sin(inc*math::deg2rad), 0);
    math::matrix<float, 4, 4> model=math::matrix_model(offset, rotation, 1);

    shawa->model_set(model);
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      local_handle.clear();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      glUseProgram(shawader->get());
      
      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "view"), 1, GL_FALSE, cam.view_get()->address());
      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "projection"), 1, GL_FALSE, cam.projection_get(window_get()->get_width()/(float)window_get()->get_height())->address());

      duplicate(offset, 10);
      
      local_handle.drop();
    }
  }
  
  void init()
  {
    graphics::gl_handle local_handle=render_handle_get();
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      vertex=new graphics::obj_shader("shaders/vertex-3d.glsl", graphics::obj_shader_type::VERTEX);
      fragment=new graphics::obj_shader("shaders/fragment-default.glsl", graphics::obj_shader_type::FRAGMENT);
      shawader=new graphics::shader(vertex, fragment);
      shawa=new graphics::textured_mesh(math::matrix_model(math::vector<float, 3>({0, 0, 2}), math::quat<float>(1, 0, 0, 0), 1), shawa_vert, shawa_i, &shawafile);
      
      glClearColor(0.5, 0.5, 0.7, 1);
      glEnable(GL_DEPTH_TEST);
      
      local_handle.drop();
    }
  }
private:
  std::vector<float> shawa_vert=
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

  std::vector<unsigned int> shawa_i=
    {
      0, 1, 2, 0, 2, 3,
      4, 5, 6, 4, 6, 7,
      8, 9, 10, 8, 10, 11,
      12, 13, 14, 12, 14, 15,
      16, 17, 18, 19, 17, 18
    };
      
  graphics::gl_handle local_handle=render_handle_get();

  unsigned int shawa_vbo;
  unsigned int shawa_vao;
  unsigned int shawa_ebo;

  file::image_loader shawafile;

  graphics::textured_mesh* shawa;

  graphics::camera cam;
  
  graphics::obj_shader* vertex;
  graphics::obj_shader* fragment;
  graphics::shader* shawader;
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
