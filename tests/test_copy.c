/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Test: write a BMP3 loaded image (copies test images)
 * and prints the image information to check it
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp_file.h"
#include "utils.h"

#define SUBDIR  "test_copy_out"

int main (void) {
    bmp3_image image;
    int errors = 0;

    make_sub_dir(SUBDIR);

    puts("");
    if (load_bmp3("detmer", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/detmer.bmp ../images/detmer.bmp

    puts("");
    if (load_bmp3("georgiou", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/georgiou.bmp ../images/georgiou.bmp
    // cmp -l test_copy_out/georgiou.bmp ../images/georgiou.bmp | gawk '{printf "%08X %02X %02X\n", $1, strtonum(0$2), strtonum(0$3)}'

    puts("");
    if (load_bmp3("burnham_spock", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/burnham_spock.bmp ../images/burnham_spock.bmp

    puts("");
    if (load_bmp3("landscape1", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/landscape1.bmp ../images/landscape1.bmp

    puts("");
    if (load_bmp3("landscape2", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/landscape2.bmp ../images/landscape2.bmp

    puts("");
    if (load_bmp3("landscape3", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/landscape3.bmp ../images/landscape3.bmp

    puts("");
    if (load_bmp3("USS_Ent", ".." DIR_SEP "images", &image)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    // diff test_copy_out/USS_Ent.bmp ../images/USS_Ent.bmp

    return errors;
}
