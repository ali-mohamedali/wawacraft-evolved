#include "libs.hpp"
#include "settings.hpp"
#include "flags.hpp"

bool flags::flag::shelled_manage(std::string g_data){
  if(option!=NULL){
    option->manage(g_data);
    return parser::SUCCESS;
  }else{
    return parser::FAILURE;
  }
}
