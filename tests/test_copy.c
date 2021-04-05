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

#define SOURCE_DIR  "images"                // source directory
#define DEST_DIR    "test_copy_out"         // destination directory

int failures = 0;

// diff test_copy_out/tested.bmp ../images/tested.bmp
// cmp -l test_copy_out/tested.bmp ../images/tested.bmp | gawk '{printf "%08X %02X %02X\n", $1, strtonum(0$2), strtonum(0$3)}'
void test(char *tested) {
    bmp3_image source;

    puts("");

    // load the image from the source directory
    if (load_bmp3(tested, ".." DIR_SEP SOURCE_DIR, &source)) {
        failures++;
        return;
    }

    // write the image in the destination directory
    if (write_bmp3(&source, DEST_DIR)) {
        failures++;
    }

    free_bmp3(&source);
}

int main (void) {

    make_sub_dir(DEST_DIR);

    test("detmer");
    test("georgiou");
    test("burnham_spock");
    test("landscape1");
    test("landscape2");

    return failures;
}
