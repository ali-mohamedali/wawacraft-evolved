#include "libs.hpp"
#include "common.hpp"
#include "settings.hpp"
#include "logging.hpp"

static settings::setting<int> logging::log::PREFIXING(PREFIX_DEFAULT, PREFIXING_SETTINGS);
static settings::setting<int> logging::log::LOGGING(LOGGING_YES, LOGGING_SETTINGS);

static settings::setting<int> logging::log::MESSAGE_LOGGING(LOGGING_YES, LOGGING_SETTINGS);
static settings::setting<int> logging::log::RECORD_LOGGING(LOGGING_NO, LOGGING_SETTINGS);
static settings::setting<int> logging::log::ERROR_LOGGING(LOGGING_YES, LOGGING_SETTINGS);

logging::log::log(std::string g_function, std::string g_scope, bool announced):
  function(g_function),
  scope(g_scope)
{
  if(announced){
    announce();
  }
}

logging::log::log(std::string g_function, std::string g_scope, std::string g_announcement):
  function(g_function),
  scope(g_scope)
{
  announce(g_announcement);
}

void logging::log::set_scope(std::string g_scope)
{
  
}

void logging::log::set_function(std::string g_function)
{
  function=g_function;
}

void logging::log::message(std::string p)
{
  if(possible()){
    print_cout(prefix()+p);
  }
}

void logging::log::record(std::string p)
{
  if(possible()){
    print_clog(prefix()+"LOG "+p);
  }
}

void logging::log::error(std::string p)
{
  if(possible()){
    print_cerr(prefix()+"ERR "+p);
  }
}

std::string logging::log::prefix()
{
  switch(PREFIXING.access()){
  case PREFIX_DEFAULT:
    return common::PROGRAM_NAME+": ";
    break;
  case PREFIX_DEBUG:
    return common::PROGRAM_NAME+": "+scope+"::"+function+"(): ";
    break;
  default:
    return common::PROGRAM_NAME+": ";
  }
}

bool logging::log::possible()
{
  return (LOGGING.access()==LOGGING_YES) ? true : false;
}

void logging::log::announce(std::string g_announcement)
{
  record(g_announcement);
}

void logging::log::print_cout(std::string p)
{
  switch(MESSAGE_LOGGING.access()){
  case LOGGING_YES:
    std::cout << p << std::endl;
    break;
  case LOGGING_NO:
    return;
    break;
  default:
    return;
    break;
  }
}

void logging::log::print_clog(std::string p)
{
  switch(RECORD_LOGGING.access()){
  case LOGGING_YES:
    std::clog << p << std::endl;
    break;
  case LOGGING_NO:
    return;
    break;
  default:
    return;
    break;
  }
}

void logging::log::print_cerr(std::string p)
{
  switch(ERROR_LOGGING.access()){
  case LOGGING_YES:
    std::cerr << p << std::endl;
    break;
  case LOGGING_NO:
    return;
    break;
  default:
    return;
    break;
  }
}
