/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Tests the BMP3 file creation (with different width), filling and writing
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

void test(char *name, int width, int height, enum color color) {
    bmp3_image image;
    char image_name[FILENAME_LEN];
    int i;

    // test of the creation with widths of which %4 has different values 
    for (i = 0; i < 4; i++) {
        puts("");

        // create a unique image name
        sprintf(image_name, "%s_%d", name, i);

        //create the image
        if (create_bmp3(&image, image_name, width+i, height)) {
            failures++;
            continue;
        }

        // if the color is not black, fill the image with the given color
        if (color) {
            fill_bmp3(&image, WHITE);
        }

        // write the image
        if (write_bmp3(&image, DEST_DIR)) {
            failures++;
        }

        // display image information
        puts("");
        print_bmp3_info(&image);
        free_bmp3(&image);
    }
}

int main (void) {

    make_sub_dir(DEST_DIR);

    test("test_landscape_black", 40, 30, BLACK);
    test("test_portrait_white", 3333, 4444, WHITE);

    return failures;
}
