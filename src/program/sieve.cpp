#include "libs.hpp"
#include "flags.hpp"
#include "logging.hpp"

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

flags::sieve::sieve(flags::synonym_table g_synonyms, flags::pseudo_table g_pseudos, int argc, char** argv)
{
  load(argc, argv);
  set_synonyms(g_synonyms);
  set_pseudos(g_pseudos);
}

flags::sieve::sieve(flags::synonym_table g_synonyms, flags::pseudo_table g_pseudos, std::vector<std::string> args):
  arguments(args)
{
  set_synonyms(g_synonyms);
  set_pseudos(g_pseudos);
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

void flags::sieve::set_pseudos(flags::pseudo_table g_pseudos)
{
  pseudos=g_pseudos;
}

flags::sequence flags::sieve::filter()
{
  arguments=replace_pseudos();
  
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

  return false;
}

flags::marker flags::sieve::get_marker(std::string g_string)
{
  return (flag(g_string)) ? FLAG : DATA;
}

std::string flags::sieve::compress_vector(std::vector<std::string> g_strings)
{
  std::string ret;

  for(std::vector<std::string>::const_iterator i=g_strings.begin(); i!=g_strings.end(); i++){
    ret+=(*i);

    if(i+1!=g_strings.end()){
      ret+=" ";
    }
  }

  return ret;
}

std::string flags::sieve::find_synonym(char g)
{
  if(synonyms.find(g)!=synonyms.end()){   
    return (synonyms.find(g))->second;
  }else{
    return "";
  }
}

std::vector<std::string> flags::sieve::find_real(std::string g)
{
  if(pseudos.find(g)!=pseudos.end()){
    std::vector<std::string> ret=(pseudos.find(g))->second;
    std::vector<std::string> rec=find_real(compress_vector(ret));

    if(rec.at(0)==""){
      return ret;
    }else{
      return rec;
    }
  }else{
    return {""};
  }
}

std::vector<std::string> flags::sieve::replace_pseudos()
{
  std::vector<std::string> ret;

  for(std::vector<std::string>::const_iterator i=arguments.begin(); i<arguments.end(); i++){
    std::vector<std::string> replacement=find_real(*i);
    
    if(replacement.at(0)!=""){
      ret.insert(ret.end(), replacement.begin(), replacement.end());
    }else{
      ret.push_back(*i);
    }
  }

  return ret;
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
  logging::log pen("expand", "flags::sieve");
  
  if(g_symbol.type==FLAG){
    if(two_dash(g_symbol.name)){
      return {g_symbol};
    }else if(g_symbol.name.size()>=2){
	flags::sequence ret;
      
	for(std::string::const_iterator i=g_symbol.name.begin()+1; i<g_symbol.name.end(); i++){
	  char n=*i;
	  std::string short_name;
	  short_name+=n;
	  std::string j=find_synonym(n);
	  
	  if(j!=""){
	    std::vector<std::string> pseudo_find=find_real(j);
	    if(pseudo_find.at(0)!=""){
	      flags::sieve inner(synonyms, pseudos, pseudo_find);
	      flags::sequence rec=inner.filter();
	      
	      ret.insert(ret.end(), rec.begin(), rec.end());
	    }else{   
	      ret.push_back({j, get_marker(j)});
	    }
	  }else{
	    pen.error("Ignored. No synonym for short-flag "+short_name);
	    continue;
	  }
	}

	return ret;
    }else{
      pen.error("Invalid flag notation! What the heck?");
      
      flags::symbol opposite={g_symbol.name, DATA};
      return {opposite};
    }
  }
  
  return {g_symbol};
}
