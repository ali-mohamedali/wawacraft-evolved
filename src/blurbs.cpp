#include "libs.hpp"
#include "program/settings.hpp"
#include "blurbs.hpp"

settings::setting<int> blurbs::help_setting(false, {}, &blurbs::help);
settings::setting<int> blurbs::version_setting(false, {}, &blurbs::version);

void blurbs::banner()
{
  std::cout << common::PROGRAM_NAME_FORMAL << " " << common::PROGRAM_VERSION
	    << "\nCopyright (C) 2024-2025 Stephen P. Hurlsmith" << std::endl;
  std::cout << common::PROGRAM_NAME_FORMAL << " is licensed under the GNU General Public License version 3."
	    << "\nSee files named LICENSE and COPYING for more information." << std::endl;
  std::cout << "\n!!! WAWACRAFT:EVOLVED FOREVER :3 !!!\n" << std::endl;
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
