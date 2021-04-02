/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Tests an image reduction (function used in the mosaic creation)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp_file.h"
#include "mosaic_filter.h"
#include "utils.h"

#define SOURCE_DIR  "images"                // source directory
#define DEST_DIR    "test_reduction_out"    // destination directory

int failures = 0;

void test(char *source_name, int *tests, int n) {
    bmp3_image source;              // source image
    bmp3_image dest;                // destination image
    int dest_width;                 // destination image width
    int dest_height;                // destination image height
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
        sprintf(dest.name, "%s_reduction_%d", source_name, tests[i]);

        // create the reduced image
        if (!tests[i]) {
            dest_width = 0;
            dest_height = 0;
        } else {
            dest_width = source.header.width/tests[i];
            dest_height = source.header.height/tests[i];
        }
        rv = reduce(&source, &dest, dest_width, dest_height, tests[i]);

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
    bmp3_image dummy;

    make_sub_dir(DEST_DIR);

    // test of the errors
    sprintf(dummy.name, "error");
    dummy.header.width = 1000;
    dummy.header.height = 100;
    reduce(&dummy, &dummy, 0, 0, 0);
    reduce(&dummy, &dummy, 200, 0, 0);
    reduce(&dummy, &dummy, 200, 200, 0);
    reduce(&dummy, &dummy, 200, 200, 2);
    reduce(&dummy, &dummy, 200, 200, 20);

    // test the reduction with the reduction factor
    test("burnham_spock", (int[]){ -10, 0, 2, 10, 20, 30, 40, 50, 100, 500, 903, 1000 }, 12);
    test("landscape1", (int[]){ -10, 0, 2, 10, 20, 30, 40, 50, 100, 500, 980, 1000 }, 12);

    return failures;
}
