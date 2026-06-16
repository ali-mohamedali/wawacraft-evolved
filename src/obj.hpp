#ifndef OBJ_H
#define OBJ_H

#include "libs.hpp"
#include "file.hpp"
#include "logging.hpp"

namespace file{
  class obj_loader:public loader{
  public:
    obj_loader(std::string);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
  private:
    void load();

    std::vector<float> texture;
    std::vector<float> vertex;
  };
}

#endif
