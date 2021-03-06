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

#define N_FACTOR        12                  // number of reduction factor values tested

int reduction_factors[N_FACTOR] = { 1, 2, 10, 20, 30, 40, 50, 100, 500, 800, 900, 1000 };

int failures = 0;

void test(char *source_name) {
    bmp3_image source;              // source image
    bmp3_image dest;                // destination image
    int dest_width;                 // destination image width
    int dest_height;                // destination image height
    int i;

    puts("");

    // load the source image from the source directory
    if (load_bmp3(source_name, ".." DIR_SEP SOURCE_DIR, &source)) {
        failures += N_FACTOR;
        return;
    }

    for (i = 0; i < N_FACTOR; i++) {
        // set the destination name
        sprintf(dest.name, "%s_reduction_%d", source_name, reduction_factors[i]);

        // create the reduced image
        if (!reduction_factors[i]) {
            dest_width = 0;
            dest_height = 0;
        } else {
            dest_width = source.header.width/reduction_factors[i];
            dest_height = source.header.height/reduction_factors[i];
        }

        // reduce the image
        if (reduce(&source, &dest, dest_width, dest_height, reduction_factors[i])) {
            failures++;
            continue;
        }

        // write the new image
        if (write_bmp3(&dest, DEST_DIR)) {
            failures++;
        }

        free_bmp3(&dest);
    }

    free_bmp3(&source);
}

int main (void) {
    bmp3_image dummy;

    make_sub_dir(DEST_DIR);

    // test the error values (don't count them in the failures count)
    sprintf(dummy.name, "error");
    dummy.header.width = 1000;
    dummy.header.height = 100;
    reduce(&dummy, &dummy, 0, 0, 0);        // invalid width
    reduce(&dummy, &dummy, 200, 0, 0);      // invalid height
    reduce(&dummy, &dummy, 200, 200, 0);    // invalid reduction factor
    reduce(&dummy, &dummy, 200, 200, 2);    // source height is not < factor * destination height
    reduce(&dummy, &dummy, 200, 200, 20);   // source width is not < factor * destination width

    // test the reduction with different reduction factor
    test("burnham_spock");
    test("landscape1");

    printf("\nerrors: %d\n", failures);
    return failures;
}
