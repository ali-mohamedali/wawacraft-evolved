#include "libs.hpp"
<<<<<<< HEAD
#include "program/settings.hpp"
#include "blurbs.hpp"
=======
#include "settings.hpp"
#include "blurbs.hpp"
#include "config.h"
>>>>>>> new_base

const int blurbs::BANNER_YES=1;
const int blurbs::BANNER_NO=0;

const std::unordered_map<std::string, int> blurbs::BANNER_TABLE=
  {
    {"yes", blurbs::BANNER_YES},
    {"no", blurbs::BANNER_NO}
  };

settings::setting<int> blurbs::banner_setting(blurbs::BANNER_YES, blurbs::BANNER_TABLE, &blurbs::banner);

settings::setting<int> blurbs::help_setting(0, {}, &blurbs::help);
settings::setting<int> blurbs::version_setting(0, {}, &blurbs::version);

void blurbs::banner()
{
  if(banner_setting.access()==BANNER_YES){
    std::cout << common::PROGRAM_NAME_FORMAL << " " << common::PROGRAM_VERSION
<<<<<<< HEAD
	      << "\nCopyright (C) 2024-2025 Stephen P. Hurlsmith" << std::endl;
  
=======
	      << "\nCopyright (C) 2024-2026 Ali Mohamed Ali AKA Stephen P. Hurlsmith" << std::endl;
>>>>>>> new_base
    std::cout << common::PROGRAM_NAME_FORMAL << " is licensed under the GNU"
	      << "\nGeneral Public License version 3. See files"
	      << "\nnamed LICENSE and COPYING for more"
	      << "\ninformation." << std::endl;
  
    std::cout << "\n!!! WAWACRAFT:EVOLVED FOREVER :3 !!!\n" << std::endl;

    banner_setting.manage("no");
  }
}

void blurbs::help()
{
<<<<<<< HEAD
  std::cout << common::PROGRAM_NAME_FORMAL << " " << common::PROGRAM_VERSION << std::endl;
  std::cout << "Help text to be added!" << std::endl;
=======
  banner();

  std::cout << "Options of the program:" << std::endl;

  int longest_option=0;
  for(int i=0; i<blurbs::help_table_size; i++){
    if(blurbs::help_table[i].flag.length()>24){
      continue;
    }else if(blurbs::help_table[i].flag.length()>longest_option){
      longest_option=blurbs::help_table[i].flag.length();
    }
  }

  for(int i=0; i<blurbs::help_table_size; i++){
    std::cout << "  "
	      << blurbs::help_table[i].flag;

    std::string concession="";
    int concession_length=(longest_option-blurbs::help_table[i].flag.length());
    if(concession_length>0){
      for(int i=0; i<concession_length; i++){
	concession+=" ";
      }
    }else{
      concession="\n  ";
      for(int i=0; i<longest_option; i++){
	concession+=" ";
      }
    }
    
    std::cout << concession
	      << blurbs::help_table[i].help << std::endl;
  }
  
>>>>>>> new_base
  std::exit(0);
}

void blurbs::version()
{
  std::cout << common::PROGRAM_NAME_FORMAL << " " << common::PROGRAM_VERSION << std::endl;
  std::exit(0);
}
