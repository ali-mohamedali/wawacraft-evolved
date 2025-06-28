#ifndef FLAGS_H
#define FLAGS_H

#include "../libs.hpp"
#include "settings.hpp"

namespace flags{
  enum marker{
    DATA=0,
    FLAG=1
  };

  struct symbol{
    std::string name;
    marker type;
  };

  typedef std::vector<symbol> sequence;
  typedef std::unordered_map<char, std::string> synonym_table;

  class sieve{
  public:
    sieve(int, char**);
    sieve(synonym_table);
    sieve(synonym_table, int, char**);
    
    void load(int, char**);
    void set_synonyms(synonym_table);
    
    sequence filter();
  
  private:
    bool flag(std::string);
    bool data(std::string);

    bool one_dash(std::string);
    bool two_dash(std::string);

    marker get_marker(std::string);

    std::string find_synonym(char);
  
    sequence categorize();
    sequence expand(symbol);
  
    synonym_table synonyms;
  
    std::vector<std::string> arguments;
  };

  struct flag{
    bool accepts_data;
    settings::setting<int>* option;

    bool shelled_manage(std::string);
  };

  typedef std::unordered_map<std::string, flag> flag_table;

  class parser{
  public:
    parser(flag_table);
  
    bool parse(sequence);

    static const bool SUCCESS=false;
    static const bool FAILURE=true;
  
    flag_table flags;
  private:
    bool is_data_first(sequence&);

    bool call_flag(flag&, std::string);

    std::string accumulate_data(flags::sequence, std::vector<flags::symbol>::const_iterator, std::vector<flags::symbol>::const_iterator);
    
    std::vector<symbol>::iterator find_flag(sequence&);
    std::vector<symbol>::iterator find_flag(sequence&, std::vector<symbol>::iterator);
    
    std::unordered_map<std::string, flag>::iterator get_record(std::string);
  };
}

#endif
