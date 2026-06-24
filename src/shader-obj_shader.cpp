#include "libs.hpp"
#include "shader.hpp"
#include "file.hpp"
#include "logging.hpp"

graphics::obj_shader::obj_shader(std::string g_path, graphics::obj_shader_type g_type):
  path(g_path),
  type(g_type)
{
  file::loader file(path);

  source=file.file_get();
  csrc=source.c_str();

  create_shader();
}

void graphics::obj_shader::create_shader()
{
  logging::log pen("create_shader", "graphics::obj_shader",
		   "Compiling runtime shader at `"+path+"`");
  
  switch(type){
  case graphics::VERTEX:
    pen.record("Vertex shader");
    id=glCreateShader(GL_VERTEX_SHADER);
    break;
  case graphics::FRAGMENT:
    pen.record("Fragment shader");
    id=glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    break;
  }

  glShaderSource(id, 1, &csrc, NULL);
  glCompileShader(id);

  int success;
  char log[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(id, 512, NULL, log);
    
    pen.error("Shader compilation failed.");
    pen.error("From OpenGL...");
    pen.error(log);
  }
}

unsigned int graphics::obj_shader::get()
{
  return id;
}
