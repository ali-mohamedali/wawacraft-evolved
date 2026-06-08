#ifndef PATH_H
#define PATH_H

#include <string>

std::string
ROOT_INSTALL_PATH()
{
    static std::string path="${prefix}/share/wawacraft-evolved";
    path.replace(path.begin(), path.begin()+9, "/usr/local");

    return path;
}

#endif
