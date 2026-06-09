#ifndef PATH_H
#define PATH_H

#include <string>

std::string
root_install_path()
{
    std::string path="${prefix}/share/wawacraft-evolved";
    path.replace(path.begin(), path.begin()+9, "/usr/local");

    return path;
}

#endif
