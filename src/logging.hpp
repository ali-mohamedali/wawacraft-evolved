#ifndef LOGGING_H
#define LOGGING_H

#include "libs.hpp"
#include "common.hpp"
#include "settings.hpp"

namespace logging{
  const int PREFIX_DEFAULT=0;
  const int PREFIX_DEBUG=1;
  
  const std::unordered_map<std::string, int> PREFIXING_SETTINGS=
    {
      {"regular", PREFIX_DEFAULT},
      {"debug", PREFIX_DEBUG},
      {"t", PREFIX_DEBUG},
      {"nil", PREFIX_DEFAULT}
    };

  const int LOGGING_YES=0;
  const int LOGGING_NO=1;
  
  const std::unordered_map<std::string, int> LOGGING_SETTINGS=
    {
      {"t", LOGGING_YES},
      {"nil", LOGGING_NO},
      {"default", LOGGING_YES},
      {"chatty", LOGGING_YES},
      {"quiet", LOGGING_NO},
      {"yes", LOGGING_YES},
      {"no", LOGGING_NO}
    };

  const std::string DEFAULT_ANNOUNCEMENT="";
  
  class log{
  public:
    explicit log(std::string, std::string);
    explicit log(std::string, std::string, bool);
    explicit log(std::string, std::string, std::string);
    
    void set_scope(std::string);
    void set_function(std::string);
  
    void message(std::string);
    void record(std::string);
    void error(std::string);

    static settings::setting<int> PREFIXING;
    static settings::setting<int> LOGGING;

    static settings::setting<int> MESSAGE_LOGGING;
    static settings::setting<int> RECORD_LOGGING;
    static settings::setting<int> ERROR_LOGGING;
    
  private:
    log();
    
    std::string prefix();

    bool possible();

    void announce(std::string);
    
    void print_cout(std::string);
    void print_clog(std::string);
    void print_cerr(std::string);
    
    std::string scope;
    std::string function;
  };
}

#endif
