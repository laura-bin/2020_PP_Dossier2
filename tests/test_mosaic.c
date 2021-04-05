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

#define N_TRANSPARENCY  4                   // number of transparency values tested
#define N_TILE_SIZE1    4                   // number of tile size values tested
#define N_TILE_SIZE2    1                   // number of tile size values tested

int transparencies[N_TRANSPARENCY] = { 2, 4, 6, 8 };
int tile_sizes1[N_TILE_SIZE1] = { 10, 30, 50, 100 };
int tile_sizes2[N_TILE_SIZE2] = { 50 };

int failures = 0;

void test(char *source_name, int *tile_sizes, int n_tile_size) {
    bmp3_image source;              // source image
    bmp3_image dest;                // destination image
    int transparency, tile_size;    // transparency and tile size indexes

    puts("");

    // load the source image from the source directory
    if (load_bmp3(source_name, ".." DIR_SEP SOURCE_DIR, &source)) {
        failures += n_tile_size * N_TRANSPARENCY;
        return;
    }

    for (tile_size = 0; tile_size < n_tile_size; tile_size++) {
        for (transparency = 0; transparency < N_TRANSPARENCY; transparency++) {
            // set the mosaic name
            sprintf(dest.name, "%s_mosaic_%d_%d", source_name, tile_sizes[tile_size], transparencies[transparency]);

            // create the mosaic
            if (create_mosaic(&source, &dest, tile_sizes[tile_size], transparencies[transparency])) {
                failures++;
                continue;
            }

            // write the mosaic
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
    create_mosaic(&dummy, &dummy, -10, 0);  // invalid tile size
    create_mosaic(&dummy, &dummy, 0, 0);    // invalid tile size
    create_mosaic(&dummy, &dummy, 10, -10); // invalid transparency
    create_mosaic(&dummy, &dummy, 10, 20);  // invalid transparency

    make_sub_dir(DEST_DIR);

    // test the mosaic creation with different tile sizes and transparencies
    test("detmer", tile_sizes1, N_TILE_SIZE1);
    test("landscape2", tile_sizes1, N_TILE_SIZE1);
    test("georgiou_mosaic_100_8", tile_sizes2, N_TILE_SIZE2);

    printf("\nerrors: %d\n", failures);
    return failures;
}
