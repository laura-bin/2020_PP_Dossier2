/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Mosaic filter
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>

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
        printf("reducing %s: factor * destination width must be > source width\n", source->name);
        return -1;
    }
    if (dest_height*factor > source->header.height) {
        printf("reducing %s: factor * destination height must be > source height\n", source->name);
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

int create_mosaic(bmp3_image *source, bmp3_image *dest, int tile_size, int transparency) {
    bmp3_image miniature;           // miniature image
    bmp3_image tile;                // tile image
    int factor;                     // reduction factor
    int dest_row, dest_col;         // destination image row and column indexes
    int tile_row, tile_col;         // tile row and column indexes
    int mini_row, mini_col;         // miniature image row and column indexes

    // check the parameters
    if (tile_size <= 0) {
        printf("creating mosaic %s: tile size must be greater than 0\n", dest->name);
        return -1;
    }
    if (transparency < 0 || transparency > 10) {
        printf("creating mosaic %s: the transparency value must be [0-%d] \n",
                    dest->name, TRANSP_SCALE);
        return -1;
    }

    // reduce the source image to the miniature:
    // (the reduction factor corresponds to the tile size)
    sprintf(miniature.name, "%s_miniature", source->name);
    if (reduce(source, &miniature, source->header.width/tile_size,
            source->header.height/tile_size, tile_size)) {
        return -1;
    }

    // create the tile image
    sprintf(tile.name, "%s_tile", source->name);
    if (source->header.width > source->header.height) {
        factor = source->header.height / tile_size;
    } else {
        factor = source->header.width / tile_size;
    }
    if (reduce(source, &tile, tile_size, tile_size, factor)) {
        return -1;
    }

    // initialize the mosaic
    if (create_bmp3(dest, miniature.header.width*tile_size, miniature.header.height*tile_size)) {
        return -1;
    }

    // set the pixel matrix colors
    // for each pixel of the miniaturized image
    for (mini_row = 0; mini_row < miniature.header.height; mini_row++) {
        for (mini_col = 0; mini_col < miniature.header.width; mini_col++) {

            // expand the pixel to the tile size in the mosaic
            for (tile_row = 0; tile_row < tile_size; tile_row++) {
                for (tile_col = 0; tile_col < tile_size; tile_col++) {
                    dest_row = tile_row + mini_row * tile_size;
                    dest_col = tile_col + mini_col * tile_size;

                    // and set the pixel color combining the average color and the tile pixel
                    dest->matrix[dest_row][dest_col].R =
                        tile.matrix[tile_row][tile_col].R * (TRANSP_SCALE - transparency) / TRANSP_SCALE
                        + miniature.matrix[mini_row][mini_col].R * transparency / TRANSP_SCALE;
                    dest->matrix[dest_row][dest_col].G =
                        tile.matrix[tile_row][tile_col].G * (TRANSP_SCALE - transparency) / TRANSP_SCALE
                        + miniature.matrix[mini_row][mini_col].G * transparency / TRANSP_SCALE;
                    dest->matrix[dest_row][dest_col].B =
                        tile.matrix[tile_row][tile_col].B * (TRANSP_SCALE - transparency) / TRANSP_SCALE
                        + miniature.matrix[mini_row][mini_col].B * transparency / TRANSP_SCALE;
                }
            }
        }
    }

    free_bmp3(&tile);
    free_bmp3(&miniature);

    return 0;
}
