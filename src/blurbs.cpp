#include "libs.hpp"
#include "program/settings.hpp"
#include "blurbs.hpp"

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
	      << "\nCopyright (C) 2024-2025 Stephen P. Hurlsmith" << std::endl;
  
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
  std::cout << common::PROGRAM_NAME_FORMAL << " " << common::PROGRAM_VERSION << std::endl;
  std::cout << "Help text to be added!" << std::endl;
  std::exit(0);
}

void blurbs::version()
{
  std::cout << common::PROGRAM_NAME_FORMAL << " " << common::PROGRAM_VERSION << std::endl;
  std::exit(0);
}
