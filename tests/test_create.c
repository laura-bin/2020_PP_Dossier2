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

#define SUBDIR  "test_create_out"

int main (void) {
    bmp3_image image;
    int errors = 0;

    make_sub_dir(SUBDIR);
    
    puts("");
    if (create_bmp3(&image, "test_landscape_black_1", 40, 30)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);
    
    puts("");
    if (create_bmp3(&image, "test_landscape_black_2", 41, 30)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);
    
    puts("");
    if (create_bmp3(&image, "test_landscape_black_3", 42, 30)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);
    
    puts("");
    if (create_bmp3(&image, "test_landscape_black_4", 43, 30)) {
        errors++;
    }
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);
    
    puts("");
    if (create_bmp3(&image, "test_portrait_white", 30, 40)) {
        errors++;
    }
    fill_bmp3(&image, WHITE);
    if (write_bmp3(&image, SUBDIR)) {
        errors++;
    }
    print_bmp3_info(&image);
    free_bmp3(&image);

    return errors;
}
