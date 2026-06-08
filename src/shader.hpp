#ifndef SHADER_H
#define SHADER_H

#include "libs.hpp"
#include "common.hpp"

namespace graphics{
  enum obj_shader_type
    {
      VERTEX,
      FRAGMENT
    };
  
  class obj_shader{
  public:
    obj_shader(std::string, obj_shader_type);
    
    unsigned int get();
  private:
    void create_shader();
    
    std::string path;
    std::string source;

    const char* csrc;

    obj_shader_type type;
    unsigned int id;
  };

  class shader{
  public:
    shader(obj_shader*, obj_shader*);

    void validate_program();
    
    unsigned int get();
  private:
    bool validate_pointers();
    
    obj_shader* vertex;
    obj_shader* fragment;
    
    unsigned int id;
  };
}

#endif
