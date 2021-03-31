/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 *
 * Utils functions:
 *  - make a subdirectory (windows and linux compatible)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <unistd.h>
#include <sys/types.h>

#ifdef _WIN32 // win 32 or win 64
#include <direct.h>     // mkdir
#endif

#ifdef __linux__
#include <sys/stat.h>   // mkdir
#endif

#include "utils.h"

int make_sub_dir(char *new_dir) {
#ifdef _WIN32
    return _mkdir(new_dir);
#else
    return mkdir(new_dir, 0700);
#endif
}
