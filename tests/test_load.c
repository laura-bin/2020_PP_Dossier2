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

#define SOURCE_DIR  "images"                // source directory
#define DEST_DIR    "test_create_out"       // destination directory

int failures = 0;

/**
 * Tests the bmp file loading function
 * and diplays the file metadata
 * 
 * @param name: name of the file (placed in DEST_DIR directory)
 */
void test(char *name) {
    bmp3_image image;

    puts("");
    if (load_bmp3(name, ".." DIR_SEP "images", &image)) {
        failures++;
    }
    puts("");
    print_bmp3_info(&image);
    free_bmp3(&image);
}

int main (void) {

    make_sub_dir(DEST_DIR);

    test("detmer");
    test("georgiou");
    test("burnham_spock");
    test("landscape1");
    test("landscape2");
    test("landscape3");

    return failures;
}
