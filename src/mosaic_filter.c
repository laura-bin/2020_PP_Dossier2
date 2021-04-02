/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Mosaic filter
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>

#include "bmp_file.h"
#include "mosaic_filter.h"

int reduce(bmp3_image *source, bmp3_image *dest, int dest_width, int dest_height, int factor) {

    int dest_row, dest_col;     // destination image row and column indexes
    int source_row, source_col; // source image row and column indexes
    int offset_row, offset_col; // row and column offsets
    int red, green, blue;       // average of colors

    // check the parameters
    if (dest_width <= 0) {
        printf("reducing %s: width must be greater than 0\n", source->name);
        return -1;
    }
    if (dest_height <= 0) {
        printf("reducing %s: height must be greater than 0\n", source->name);
        return -1;
    }
    if (factor <= 0) {
        printf("reducing %s: reduction factor must be greater than 0\n", source->name);
        return -1;
    }
    if (dest_width*factor > source->header.width) {
        printf("reducing %s: factor * destination width > source width\n", source->name);
        return -1;
    }
    if (dest_height*factor > source->header.height) {
        printf("reducing %s: factor * destination height > source height\n", source->name);
        return -1;
    }

    // compute the offsets (if the image must be cropped, the four sizes are cropped)
    offset_row = (source->header.height - dest_height*factor) / 2;
    offset_col = (source->header.width - dest_width*factor) / 2;

    // create the new image
    if (create_bmp3(dest, dest_width, dest_height)) {
        return -1;
    }

    // set the pixel matrix colors
    for (dest_row = 0; dest_row < dest->header.height; dest_row++) {
        for (dest_col = 0; dest_col < dest->header.width; dest_col++) {
            red = 0;
            green = 0;
            blue = 0;

            // compute the average of colors for each pixel of the image
            for (source_row = dest_row*factor; source_row < dest_row*factor + factor; source_row++) {
                for (source_col = dest_col*factor; source_col < dest_col*factor + factor; source_col++) {
                    red += source->matrix[source_row+offset_row][source_col+offset_col].R;
                    green += source->matrix[source_row+offset_row][source_col+offset_col].G;
                    blue += source->matrix[source_row+offset_row][source_col+offset_col].B;
                }
            }

            // write the computed colors in the reduced image
            dest->matrix[dest_row][dest_col].R = red / (factor*factor);
            dest->matrix[dest_row][dest_col].G = green / (factor*factor);
            dest->matrix[dest_row][dest_col].B = blue / (factor*factor);
        }
    }

    return 0;
}
