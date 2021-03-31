#pragma once
/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 *
 * Utils functions:
 *  - make a subdirectory (windows and linux compatible)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>

/* Directory separator */
#ifdef _WIN32
#define DIR_SEP "\\"
#else
#define DIR_SEP "/"
#endif

/**
 * Makes a new directory in the directory from which the program is launched
 * 
 * @return mkdir or _mkdir return value:
 *          0 if the directory was successfully created
 *         -1 if an error occured & set errno
 */
int make_sub_dir(char *new_dir);
