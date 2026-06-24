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
#include "obj.hpp"
#include "voxel.hpp"
#include "../config.h"

float inc=0;

class test_node: public windows::node{
public:
  test_node(const windows::window& g_window):
    node(g_window),
    shawafile("textures/spritesheet.png"),
    cam(math::vector<float, 3>({0, 0, 0}), math::quat<float>(cos(0), 0, 0, sin(0)), 50, 1, 800)
  {
    init();
  }

  ~test_node()
  {
    delete vertex;
    delete fragment;
    delete shawader;
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
      cam.rotate(0, 2*(speed*wtime::now()), 0);
    }
    if(down.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, -2*(speed*wtime::now()), 0);
    }
    if(left.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 0, 2*(speed*wtime::now()));
    }
    if(right.state==events::keyboard::KB_KEY_PRESSED){
      cam.rotate(0, 0, -2*(speed*wtime::now()));
    }

    cam.position_set(p);
  }
  
  void window_respond(events::keyboard::event given)
  {
    quickly();
    graphics::gl_handle local_handle=render_handle_get();
    static world::voxel_type cursor_type=world::VOX_NONE;

    local_handle.hold();
    if(given.state==events::keyboard::KB_KEY_PRESSED){
      if(given.bkey==events::keyboard::KB_KEY_ENTER){
	world::voxel& v=chunks->raycast(cam.position_get(), cam.forward_get(), common::signals::YES);
	v.type_set(1+cursor_type);
	v.presence_set(common::signals::YES);
	
      }else if(given.bkey==events::keyboard::KB_KEY_BACKSPACE){
	chunks->raycast(cam.position_get(), cam.forward_get()).presence_set(common::signals::NO);
      }else if(given.bkey==events::keyboard::KB_KEY_TAB){
	cursor_type=((((int)cursor_type)+1)%6);
      }
    }
    local_handle.drop();
  }
  
  void window_update()
  {
    logging::log pen("window_update", "test_node", false);

    inc+=25*wtime::now();

    quickly();
    wtime::reset();
    
    if(local_handle.hold()==graphics::gl_handle::SUCCESS){
      local_handle.clear();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      glUseProgram(shawader->get());
      
      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "view"), 1, GL_FALSE, cam.view_get()->address());
      glUniformMatrix4fv(glGetUniformLocation(shawader->get(), "projection"), 1, GL_FALSE, cam.projection_get(window_get()->get_width()/(float)window_get()->get_height())->address());

      chunks->raycast(cam.position_get(), cam.forward_get(), common::signals::YES);
      chunks->render(cam.position_get());
      
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

      chunks=new world::chunk_scheme(&shawafile);
      
      glClearColor(0.5, 0.5, 0.7, 1);

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      
      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      glFrontFace(GL_CW);
      
      local_handle.drop();
    }
  }
private:      
  graphics::gl_handle local_handle=render_handle_get();

  unsigned int shawa_vbo;
  unsigned int shawa_vao;
  unsigned int shawa_ebo;

  file::image_loader shawafile;

  world::chunk_scheme* chunks;

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

  test_node* my_win=new test_node(windows::window(640, 480, "Wawacraft:Evolved v"+common::PROGRAM_VERSION+" [Satisfaction]"));

  manager.nodes_add(my_win);
  
  while(manager.nodes_present()){
    manager.cycle();
  }
  
  windows::reserve::end();
  
  return 0;
}
