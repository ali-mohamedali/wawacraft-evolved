#include "libs.hpp"
#include "settings.hpp"
#include "logging.hpp"
#include "flags.hpp"

static const bool flags::parser::SUCCESS=common::signals::SUCCESS;
static const bool flags::parser::FAILURE=common::signals::FAILURE;

flags::parser::parser(flags::flag_table g_flags):
  flags(g_flags)
{
  
}

bool flags::parser::parse(flags::sequence g_sequence)
{
  logging::log pen("parse", "flags::parser");
  
  if(is_data_first(g_sequence)==FAILURE){
    return FAILURE;
  }

  std::vector<flags::symbol>::iterator flag=g_sequence.begin();
  while(flag<g_sequence.end()){
    std::vector<flags::symbol>::iterator range=find_flag(g_sequence, flag);

    std::unordered_map<std::string, flags::flag>::iterator record=get_record(flag->name);
    if(record!=flags.end()){
      if(range==flag+1){
	bool call=call_flag(record->second, "");

	if(call==FAILURE){
	  pen.error("Flag "+flag->name+" expects data but was not given any.");
	  return FAILURE;
	}
      }else{
        bool call=call_flag(record->second, accumulate_data(g_sequence, flag, range));

	if(call==FAILURE){
	  pen.error("Flag "+flag->name+" was given malformed data.");
	  return FAILURE;
	}
      }
    }else{
      return FAILURE;
    }
    
    flag=range;
  }

  return SUCCESS;
}

bool flags::parser::is_data_first(flags::sequence& g_sequence)
{
  logging::log pen("is_data_first", "flags::parser");
  
  if(g_sequence.size()>=1){
    if(g_sequence[0].type==FLAG){
      return SUCCESS;
    }
    
    pen.error("First valid symbol is not a flag.");
    return FAILURE;
  }
  
  return SUCCESS;
}

bool flags::parser::call_flag(flags::flag& g_flag, std::string data)
{
  if(g_flag.accepts_data && data!=""){
    g_flag.shelled_manage(data);
    return SUCCESS;
  }else if(!(g_flag.accepts_data) && data==""){
    g_flag.shelled_manage(data);
    return SUCCESS;
  }

  return FAILURE;
}

std::string flags::parser::accumulate_data(flags::sequence g_sequence, std::vector<flags::symbol>::const_iterator start, std::vector<flags::symbol>::const_iterator end)
{
  start++;
  
  std::string accumulate="";
  for(std::vector<flags::symbol>::const_iterator i=start; i<end; i++){
    if(i->type==DATA){
      if(i==start){
	accumulate+=i->name;
      }else{
	accumulate+=" "+i->name;
      }
    }else{
      break;
    }
  }

  return accumulate;
}

std::vector<flags::symbol>::iterator flags::parser::find_flag(flags::sequence& g_sequence)
{
  return find_flag(g_sequence, g_sequence.begin());
}

std::vector<flags::symbol>::iterator flags::parser::find_flag(flags::sequence& g_sequence, std::vector<flags::symbol>::iterator begin)
{
  for(std::vector<flags::symbol>::iterator i=begin+1; i<g_sequence.end(); i++){
    if(i->type==FLAG){
      return i;
    }
  }

  return g_sequence.end();
}

std::unordered_map<std::string, flags::flag>::iterator flags::parser::get_record(std::string g_key)
{
  logging::log pen("get_record", "flags::parser");
  
  std::unordered_map<std::string, flags::flag>::iterator ret=flags.find(g_key);
  if(ret==flags.end()){
    pen.error("No matching flag for "+g_key+".");
  }
  
  return ret;
}
