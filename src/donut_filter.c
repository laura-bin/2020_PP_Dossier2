/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Donut filter
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <math.h>
#include <stdio.h>

#include "donut_filter.h"

int create_donut(bmp3_image *source, bmp3_image *dest, int radius, double spread, enum color background) {
    int row, col;               // donut row and column indexes
    double center_x, center_y;  // coordinates of the center of the donut used as offsets for the translation
    double x, y;                // pixel coordinates adjusted with the translation
    double dist;                // distance between the pixel and the center of the donut
    int source_row, source_col; // source image row and column indexes
    int height, width;          // donut height and width

    // check the parameters
    if (radius < 0) {
        printf("creating donut %s: radius must be >= 0\n", dest->name);
        return -1;
    }
    if (spread <= 0.0 || spread > 1.0) {
        printf("creating donut %s: spread must be ]0.0-1.0]\n", dest->name);
        return -1;
    }

    // compute the donut width
    if (spread < 0.5) {
        width = 2.0 * sin(spread * M_PI) * (radius + source->header.height) + 1;
    } else {
        width = (source->header.height + radius) * 2;
    }

    // compute the donut height
    if (spread <= 0.5) {
        height = source->header.height + radius - radius * cos(spread * M_PI);
    } else if (spread < 1.0 ){
        height = (sin(M_PI * spread - M_PI / 2.0) + 1.0) * (double)(source->header.height + radius) + 1;
    } else {
        height = 2 * (source->header.height + radius);
    }

    // compute the donut center
    center_y = (double)width / 2.0 - 0.5;
    if (spread <= 0.5) {
        center_x = (double)(height - source->header.height - radius);
    } else {
        center_x = (double)height - center_y - 1.0;
    }

    // initialize the mosaic
    if (create_bmp3(dest, width, height)) {
        return -1;
    }

    // fill the background with the given color
    fill_bmp3(dest, background);

    // set the donut pixel
    for (row = 0; row < height; row++) {
        for (col = 0; col < dest->header.width; col++) {
            x = (double)row - center_x;
            y = (double)col - center_y;
            dist = sqrt(x*x + y*y + 1);

            // if the pixel is into the donut
            if (dist > radius && dist < radius + source->header.height) {
                source_row = dist - radius;
                source_col = atan2(y, x) * ((double)source->header.width - 1.0) / 2.0 / M_PI / spread
                                + (double)source->header.width / 2.0;
                
                // and if the corresponding pixel in the source image is valid
                if (source_row > 0 && source_row < source->header.height
                    && source_col >= 0 && source_col < source->header.width) {
                    dest->matrix[row][col] = source->matrix[source_row][source_col];
                }
            }
        }
    }

    return 0;
}
