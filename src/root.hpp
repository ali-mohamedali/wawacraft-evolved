#ifndef ROOT_H
#define ROOT_H

#include "libs.hpp"
#include "logging.hpp"
#include "common.hpp"

namespace file{
  class root_path{
  public:
    root_path();
    ~root_path();

    static void suggest(std::string);
    static void suggest(std::vector<std::string>);

    static std::string get();
    static std::string qualify(std::string);

    static bool test(std::string);
    
  private:
    static std::string get_first();

    static std::string found;    
    static std::string local;
    static std::string installed;
    
    static std::vector<std::string> given;
  };
}

#endif
