#pragma once
/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Bitmap3 (24 bits) image information and manipulation:
 *  - pixel structure (RGB info)
 *  - BMP3 file information structure
 *  - BPM3 file header structure
 *  - BPM3 image structure
 *  - enum colors and colors array
 *  - load an BMP in RAM memory
 *  - print a loaded BMP information
 *  - write a BMP image loaded in RAM memory into a BMP file
 *  - create a BMP image
 *  - fill a BMP image with a given color
 * 
 * Convert image to bmp24 without compression:
 *  convert in.format -define bmp:format=bmp3 -compress none out.bmp
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#define BMP3_BPP            24      // BMP3 bit per pixel
#define BMP3_IMAGE_OFFSET   54      // BMP3 image offset

#define FILENAME_LEN        64

/* Pixel structure */
typedef struct {
    unsigned char B;    // blue
    unsigned char G;    // green
    unsigned char R;    // red
} pixel;

/* BMP file information /!\ padding */
typedef struct {
    char id[2];             // 2 bytes (BM 424D): identifies the BMP file
    unsigned file_size;     // 4 bytes: the size of the BMP file in bytes
    char application[4];    // 4 bytes: actual value depends on the application that creates the image, if created manually can be 0
    unsigned offset;        // 4 bytes: the offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found
} bmp_file_info;

/* BMP file header */
typedef struct {
    unsigned header_size;   // 4 bytes: the size of this header (after the file information), in bytes (must be 40)
    int width;              // 4 bytes: the bitmap width in pixels (signed integer)
    int height;             // 4 bytes: the bitmap height in pixels (signed integer)
    unsigned short planes;  // 2 bytes: the number of color planes (must be 1)
    unsigned short bpp;     // 2 bytes: the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32.
    unsigned compression;   // 4 bytes: the compression method being used (0 for none)
    unsigned image_size;    // 4 bytes: the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
    int horizontal_res;     // 4 bytes: the horizontal resolution of the image (pixel per metre, signed integer)
    int vertical_res;       // 4 bytes: the vertical resolution of the image (pixel per metre, signed integer)
    unsigned n_colors;      // 4 bytes: the number of colors in the color palette, or 0 to default to 2n
    unsigned n_imp_colors;  // 4 bytes: the number of important colors used, or 0 when every color is important; generally ignored 
} bmp3_header;

/* BMP image structure */
typedef struct {
    bmp_file_info file_info;    // file information
    bmp3_header header;         // file header
    char name[FILENAME_LEN];    // file name without extension
    pixel **matrix;             // pixel matrix
    unsigned pixel_count;       // number of pixel in the matrix
} bmp3_image;

/* Colors names and array of pixels */
enum color {
    BLACK,
    WHITE,
    COLOR_COUNT
};
extern const pixel colors[COLOR_COUNT];

/**
 * Loads a BMP3 file in RAM memory
 * 
 * @param name: image name
 * @param dir: BMP file directory
 * @param out_image: image read
 * 
 * @return either
 *      0 if the file has sucessfully been read
 *     -1 if an error occured
 */
int load_bmp3(char *name, char *dir, bmp3_image *out_image);

/**
 * Frees the memory dynamically allocated to store a BMP3 image in RAM memory
 * 
 * @param image: image to free
 */
void free_bmp3(bmp3_image *image);

/**
 * Prints the BMP3 image information & header
 * 
 * @param image: image loaded in RAM memory
 */
void print_bmp3_info(bmp3_image *image);

/**
 * Writes a BMP3 image stored in RAM in a new file
 * 
 * @param image: image to write
 * @param dir: relative directory in which create the new BMP file
 * 
 * @return either
 *      0 if the image has succesfully been writen
 *     -1 if an error occured
 */
int write_bmp3(bmp3_image *image, char *dir);

/**
 * Creates a new BMP3 image: pixels are set to 0 (black)
 * 
 * @param out_image: image to create
 * @param width: image width
 * @param height: image height
 * 
 * @return either
 *      0 if the image has successfully been created
 *     -1 if an error occured
 */
int create_bmp3(bmp3_image *out_image, int width, int height);

/**
 * Fills the pixel matrix with a given color
 * 
 * @param image: image in which fill the matrix
 * @param color: color with which fill the matrix
 */
void fill_bmp3(bmp3_image *image, enum color color);
