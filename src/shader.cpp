#include "libs.hpp"
#include "shader.hpp"
#include "logging.hpp"

graphics::shader::shader(graphics::obj_shader* g_vertex, graphics::obj_shader* g_fragment):
  vertex(g_vertex),
  fragment(g_fragment)
{
  logging::log pen("shader", "graphics::shader", "Creating a runtime shader program.");
  
  id=glCreateProgram();

  if(validate_pointers()){
    pen.record("Linking program");
    glAttachShader(id, vertex->get());
    glAttachShader(id, fragment->get());
    glLinkProgram(id);

    int success;
    char log[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
      glGetProgramInfoLog(id, 512, NULL, log);

      pen.error("Shader linkage ruined!");
      pen.error("From OpenGL: ");
      pen.error(log);
    }
  }

  validate_program();
}

unsigned int graphics::shader::get()
{
  return id;
}

void graphics::shader::validate_program()
{
  logging::log pen("validate_program", "graphics::shader", "Validating runtime shader program.");
  glValidateProgram(id);

  int status;
  char log[512];
  glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
  if(!status){
    glGetProgramInfoLog(id, 512, NULL, log);
    pen.error("Program is not valid!");
    pen.error("From OpenGL...");
    pen.error(log);
  }
}

bool graphics::shader::validate_pointers()
{
  logging::log pen("validate_pointers", "graphics::shader", "Validating given pointers.");

  if(vertex==NULL){
    pen.error("Vertex shader object pointer invalid!");
    return false;
  }else if(fragment==NULL){
    pen.error("Fragment shader object pointer invalid!");
    return false;
  }
  
  pen.record("All pointers valid.");

  return true;
}
