/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Tests the donut creation
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp_file.h"
#include "donut_filter.h"
#include "utils.h"

#define SOURCE_DIR  "images"                // source directory
#define DEST_DIR    "test_donut_out"        // destination directory

#define N_RADIUS    6                       // number of radius values tested
#define N_SPREAD    5                       // number of spread values tested

int radius[N_RADIUS] = { 0, 10, 50, 100, 250, 500 };
double spread[N_SPREAD] = { 0.25, 0.33, 0.5, 0.99999999999, 1.0, };

int failures = 0;

void test(char *source_name, enum color background) {
    bmp3_image source;  // source image
    bmp3_image dest;    // destination image (donut)
    int s, r;           // spread an radius indexes

    puts("");

    // load the source image from the source directory
    if (load_bmp3(source_name, ".." DIR_SEP SOURCE_DIR, &source)) {
        failures += N_RADIUS * N_SPREAD;
        return;
    }

    for (s = 0; s < N_SPREAD; s++) {
        for (r = 0; r < N_RADIUS; r++) {
            sprintf(dest.name, "%s_donut_%1.0lf_%d", source.name, spread[s]*100, radius[r]);
            if (create_donut(&source, &dest, radius[r], spread[s], background)) {
                failures++;
                continue;
            }
            if (write_bmp3(&dest, DEST_DIR)) {
                failures++;
            }
            free_bmp3(&dest);
        }
    }
    
    free_bmp3(&source);
}

int main (void) {
    bmp3_image dummy;

    make_sub_dir(DEST_DIR);

    // test the error values (don't count them in the failures count)
    sprintf(dummy.name, "error");
    dummy.header.width = 1920;
    dummy.header.height = 1080;
    create_donut(&dummy, &dummy, -10, 0.0, BLACK);      // invalid radius
    create_donut(&dummy, &dummy, 0, -12.0, BLACK);      // invalid spread
    create_donut(&dummy, &dummy, 0, 0.0, BLACK);        // invalid spread
    create_donut(&dummy, &dummy, 0, 1.00000001, BLACK); // invalid spread

    test("landscape2", MAGENTA1);
    test("landscape1", CYAN1);

    printf("\nerrors: %d\n", failures);
    return failures;
}
