#pragma once
/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Mosaic filter
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "bmp_file.h"

#define TRANSP_SCALE    10      // transparency scale

/**
 * Reduces a BMP3 image: this function is used in the mosaic creation 
 * to compute the colors of the tiles and to generate the tile image
 * 
 * @param source: source image to reduce
 * @param dest: destination image (reduced image)
 * @param dest_width: width of the reduced image
 * @param dest_height: height of the reduced image
 * @param factor: reduction factor
 * 
 * @return either
 *      0 if the image has successfully been reduced
 *     -1 if a parameter is invalid or if an error occured
 */
int reduce(bmp3_image *source, bmp3_image *dest, int dest_width, int dest_height, int factor);

/**
 * Moisaic creation :
 * the source image is transformed with tiles containing a reduction of itself
 * 
 * @param source: source image
 * @param dest: destination image (mosaic generated by this filter)
 * @param tile_size: size in pixel of the tiles of the mosaic
 * @param transparency: tile transparency between 0 (plain color) and 10 (fully transparent)
 */
int create_mosaic(bmp3_image *source, bmp3_image *dest, int tile_size, int transparency);
