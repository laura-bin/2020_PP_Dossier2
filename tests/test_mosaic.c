/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Tests the mosaic creation with a given tile size
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp_file.h"
#include "mosaic_filter.h"
#include "utils.h"

#define SOURCE_DIR  "images"                // source directory
#define DEST_DIR    "test_mosaic_out"       // destination directory

int failures = 0;

void test(char *source_name, int *tests, int n) {
    bmp3_image source;              // source image
    bmp3_image dest;                // destination image
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
        sprintf(dest.name, "%s_mosaic_%d_%d", source_name, tests[i], i);

        rv = create_mosaic(&source, &dest, tests[i], i);

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

    // test the mosaic creation with different tile sizes
    test("detmer", (int[]){ -10, 0, 2, 10, 20, 30, 40, 50, 100, 500, 900, 10000 }, 12);
    test("landscape3", (int[]){ 1000, 500, 200, 100, 50, 40, 30, 25, 20, 15, 10, 5 }, 12);
    test("georgiou", (int[]){ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }, 11);
    test("georgiou_mosaic_100_8", (int[]){ 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50 }, 11);

    return failures;
}
