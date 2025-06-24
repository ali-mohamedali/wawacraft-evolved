#include "libs.hpp"
#include "flags.hpp"

flags::sieve::sieve(int argc, char** argv)
{
  load(argc, argv);
}

flags::sieve::sieve(flags::synonym_table g_synonyms)
{
  set_synonyms(g_synonyms);
}

flags::sieve::sieve(flags::synonym_table g_synonyms, int argc, char** argv)
{
  load(argc, argv);
  set_synonyms(g_synonyms);
}

void flags::sieve::load(int argc, char** argv)
{
  for(int i=1; i<argc; i++){
    arguments.push_back(std::string(argv[i]));
  }
}

void flags::sieve::set_synonyms(flags::synonym_table g_synonyms)
{
  synonyms=g_synonyms;
}

flags::sequence flags::sieve::filter()
{
  flags::sequence first_sequence=categorize();

  flags::sequence second_sequence;
  for(std::vector<flags::symbol>::iterator i=first_sequence.begin(); i<first_sequence.end(); i++){
    flags::sequence seq=expand(*i);
    
    for(std::vector<flags::symbol>::iterator j=seq.begin(); j<seq.end(); j++){
      second_sequence.push_back(*j);
    } 
  }

  return second_sequence;
}

bool flags::sieve::flag(std::string g_string)
{
  return g_string[0]=='-';
}

bool flags::sieve::data(std::string g_string)
{
  return !(flag(g_string));
}

bool flags::sieve::one_dash(std::string g_string)
{
  return flag(g_string);
}

bool flags::sieve::two_dash(std::string g_string)
{
  if(g_string.size()>=2){
    return (one_dash(g_string) && g_string[1]=='-');
  }
}

flags::marker flags::sieve::get_marker(std::string g_string)
{
  return (flag(g_string)) ? FLAG : DATA;
}

std::string flags::sieve::find_synonym(char g)
{
  if(synonyms.find(g)!=synonyms.end()){
    return (synonyms.find(g))->second;
  }else{
    return "";
  }
}

flags::sequence flags::sieve::categorize()
{
  flags::sequence ret;
  
  for(std::vector<std::string>::const_iterator i=arguments.begin(); i<arguments.end(); i++){
    flags::symbol sym={*i, get_marker(*i)};
    
    ret.push_back(sym);
  }

  return ret;
}

flags::sequence flags::sieve::expand(flags::symbol g_symbol)
{
  if(g_symbol.type==FLAG){
    if(two_dash(g_symbol.name)){
      return {g_symbol};
    }else if(g_symbol.name.size()>=2){
	flags::sequence ret;
      
	for(std::string::const_iterator i=g_symbol.name.begin()+1; i<g_symbol.name.end(); i++){
	  std::string j=find_synonym(*i);

	  if(j!=""){
	    ret.push_back({j, get_marker(j)});
	  }else{
	    continue;
	  }
	}

	return ret;
    }else{
      flags::symbol opposite={g_symbol.name, DATA};
      return {opposite};
    }
  }
  
  return {g_symbol};
}
