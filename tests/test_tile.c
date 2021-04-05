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

#define N_TILE_SIZE     12                  // number of tile size values tests

int tile_sizes[N_TILE_SIZE] = { 1, 2, 10, 20, 30, 40, 50, 75, 100, 500, 800, 1000 };

int failures = 0;

void test(char *source_name) {
    bmp3_image source;              // source image
    bmp3_image dest;                // destination image
    int factor;                     // reduction factor
    int i;

    puts("");

    // load the source image from the source directory
    if (load_bmp3(source_name, ".." DIR_SEP SOURCE_DIR, &source)) {
        failures += N_TILE_SIZE;
        return;
    }

    for (i = 0; i < N_TILE_SIZE; i++) {
        // set the destination name
        sprintf(dest.name, "%s_tile_%d", source_name, tile_sizes[i]);

        // compute the reduction factor
        factor = 0;
        if (tile_sizes[i]) {
            if (source.header.width > source.header.height) {
                factor = source.header.height / tile_sizes[i];
            } else {
                factor = source.header.width / tile_sizes[i];
            }
        }

        // create the tile
        if (reduce(&source, &dest, tile_sizes[i], tile_sizes[i], factor)) {
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

    make_sub_dir(DEST_DIR);

    // test the file creation with different tile sizes
    test("burnham_spock");
    test("landscape1");

    return failures;
}
