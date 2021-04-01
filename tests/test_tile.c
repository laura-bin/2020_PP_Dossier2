/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Tests the tile creation using the reduction function (the tile is always a square)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp_file.h"
#include "mosaic_filter.h"
#include "utils.h"

#define SOURCE_DIR  "images"                // source directory
#define DEST_DIR    "test_tile_out"         // destination directory

int failures = 0;

void test(char *source_name, int *tests, int n) {
    bmp3_image source;              // source image
    bmp3_image dest;                // destination image
    char dest_name[FILENAME_LEN];   // destination name
    int factor;                     // reduction factor
    int rv = 0;                     // return value
    int i;

    puts("");

    // load the source image from the source directory
    if (load_bmp3(source_name, ".." DIR_SEP SOURCE_DIR, &source)) {
        failures += n;
        return;
    }

    for (i = 0; i < n; i++) {
        // set the destination name
        sprintf(dest_name, "%s_tile_%u", source_name, tests[i]);
        factor = 0;

        // create the reduced image
        if (tests[i]) {
            if (source.header.width > source.header.height) {
                factor = source.header.height / tests[i];
            } else {
                factor = source.header.width / tests[i];
            }
        }

        rv = reduce(&source, &dest, dest_name, tests[i], tests[i], factor);

        if (rv) {
            failures++;
            continue;
        }

        // write the new image
        rv = write_bmp3(&dest, DEST_DIR);
        free_bmp3(&dest);
    }
    
    free_bmp3(&source);
}

int main (void) {

    make_sub_dir(DEST_DIR);

    // test the file creation with the tile size
    test("burnham_spock", (int[]){ -10, 0, 2, 10, 20, 30, 40, 50, 100, 500, 900, 10000 }, 12);
    test("landscape1", (int[]){ -10, 0, 2, 10, 20, 30, 40, 50, 100, 500, 900, 10000 }, 12);

    return failures;
}
