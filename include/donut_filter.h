#pragma once
/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Donut filter
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

/**
 * Creates a donut image
 * 
 * @param source: source image
 * @param dest: destination image (donut)
 * @param radius: internal radius of the donut
 * @param spread: donut spread, percentage between ]0, 1]
 * @param background: background color
 * 
 * @return either
 *      0 if the donut has successfully been created
 *     -1 if a parameter is invalid or if an error occured
 */
int create_donut(bmp3_image *source, bmp3_image *dest, int radius, double spread, enum color background);
