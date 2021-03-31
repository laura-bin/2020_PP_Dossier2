/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Tests the BMP3 file loading
 * and prints the image information to check it
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp_file.h"
#include "utils.h"

int main (void) {
    bmp3_image image;
    int errors = 0;

    puts("");
    if (load_bmp3("detmer", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    puts("");
    if (load_bmp3("georgiou", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    puts("");
    if (load_bmp3("burnham_spock", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    puts("");
    if (load_bmp3("landscape1", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    puts("");
    if (load_bmp3("landscape2", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    puts("");
    if (load_bmp3("landscape3", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    puts("");
    if (load_bmp3("USS_Ent", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    return errors;
}
