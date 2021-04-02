/** *************************************************************************************
 * Dossier 2 : Transformations d’images bitmap
 * ===========================================
 * 
 * Bitmap3 (24 bits) image manipulation:
 *  - colors array assignation
 *  - load an BMP in RAM memory
 *  - print a loaded BMP information
 *  - write a BMP image loaded in RAM memory into a BMP file
 *  - create a BMP image
 *  - fill a BMP image with a given color
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp_file.h"
#include "utils.h"

/* COLORS ASSIGNATION */

const pixel colors[COLOR_COUNT] = {
    { 0, 0, 0 },
    { 255, 255, 255}
};

/* PRIVATE FUNCTION */

/**
 * Allocates the memory to a BMP3 pixel matrix
 * 
 * @param img: image for which allocate the memory
 * 
 * @return either
 *      0 if the matrix has successfully been created
 *     -1 if an error occured
 */
int alloc_pixel_matrix(bmp3_image *img) {
    int i;

    // allocate memory for the matrix rows
    if ((img->matrix = (pixel **)malloc(sizeof(void *) * img->header.height)) == NULL) {
        return -1;
    }

    // allocate memory for each pixel of each row
    for (i = 0; i < img->header.height; i++) {
        if ((img->matrix[i] = (pixel *)malloc(sizeof(pixel) * img->header.width)) == NULL) {
            return -1;
        }
    }

    return 0;
}

/**
 * Frees the memory allocated to the pixel matrix
 * and sets the matrix to NULL
 */
void free_pixel_matrix(bmp3_image *img) {
    int i;

    for (i = 0; i < img->header.height; i++) {
        free(img->matrix[i]);
    }
    free(img->matrix);
    img->matrix = NULL;
}

/* HEADER IMPLEMENTATION */

int load_bmp3(char *name, char *dir, bmp3_image *out_image) {
    char file_path[255];    // bitmap file path
    FILE *bmp_file = NULL;  // bitmap file pointer
    long line_offset;       // line buffer
    size_t line_length;     // line length (multiple of 4)
    int i;                  // line index

    // set the file path
    sprintf(file_path, "%s" DIR_SEP "%s.bmp", dir, name);
    printf("loading %s... ", file_path);

    // open the file
    if ((bmp_file = fopen(file_path, "rb")) == NULL) {
        printf("error on bitmap file opening (%s)\n", strerror(errno));
        return -1;
    }

    // set the image name
    strcpy(out_image->name, name);

    // load the file information (load id separately to avoid padding error)
    fseek(bmp_file, 0, SEEK_SET);
    memset(&out_image->file_info, 0, sizeof(bmp_file_info));
    if (fread(&out_image->file_info.id, sizeof(char), 2, bmp_file) != 2) {
        printf("error on reading id\n");
        return -1;
    }
    if (fread(((char *)&out_image->file_info)+4, sizeof(bmp_file_info) - 4, 1, bmp_file) != 1) {
        printf("error on reading file information\n");
        return -1;
    }

    // load the file header
    memset(&out_image->header, 0, sizeof(bmp3_header));
    if (fread(&out_image->header, sizeof(bmp3_header), 1, bmp_file) != 1) {
        printf("error on reading file information\n");
        return -1;
    }

    // allocate memory to the pixel matrix
    out_image->pixel_count = out_image->header.width * out_image->header.height;
    if (alloc_pixel_matrix(out_image)) {
        printf("error on pixel matrix creation (%s)\n", strerror(errno));
        return -1;
    }

    // load the pixel matrix
    line_offset = BMP3_IMAGE_OFFSET;
    line_length = 3 * out_image->header.width + out_image->header.width % 4;
    for (i = 0; i < out_image->header.height; i++) {
        fseek(bmp_file, line_offset, SEEK_SET);
        if (fread(out_image->matrix[i], 3 * out_image->header.width, 1, bmp_file) != 1) {
            printf("error on reading line %d\n", i);
            return -1;
        }
        line_offset += line_length;
    }

    fclose(bmp_file);
    printf("success\n");
    return 0;
}

void free_bmp3(bmp3_image *image) {
    free_pixel_matrix(image);
}

void print_bmp3_info(bmp3_image *image) {
    printf("%s.bmp header information:\n\n", image->name);
    printf("%-28s %s\n", "id", image->file_info.id);
    printf("%-28s %u\n", "file size (bytes)", image->file_info.file_size);
    printf("%-28s %s\n", "application", image->file_info.application);
    printf("%-28s %u\n", "offset", image->file_info.offset);
    printf("%-28s %u\n", "header size", image->header.header_size);
    printf("%-28s %d\n", "width", image->header.width);
    printf("%-28s %d\n", "height", image->header.height);
    printf("%-28s %u\n", "planes", image->header.planes);
    printf("%-28s %u\n", "bit per pixel", image->header.bpp);
    printf("%-28s %u\n", "compression", image->header.compression);
    printf("%-28s %u\n", "image size", image->header.image_size);
    printf("%-28s %d\n", "horizontal resolution", image->header.horizontal_res);
    printf("%-28s %d\n", "vertical resolution", image->header.vertical_res);
    printf("%-28s %u\n", "number of colors", image->header.n_colors);
    printf("%-28s %u\n", "number of important colors", image->header.n_imp_colors);
}

int write_bmp3(bmp3_image *image, char *dir) {
    char file_path[255];    // bitmap file path
    FILE *bmp_file = NULL;  // bitmap file pointer
    pixel *line;            // line buffer
    size_t line_length;     // line length (multiple of 4)
    int i;                  // line index

    // set the file path
    sprintf(file_path, "%s" DIR_SEP "%s.bmp", dir, image->name);
    printf("writing %s... ", file_path);

    // open the file
    if ((bmp_file = fopen(file_path, "wb")) == NULL) {
        printf("error on file opening (%s)\n", strerror(errno));
        return -1;
    }

    // write the file information (write id separately to avoid padding error)
    fseek(bmp_file, 0, SEEK_SET);
    if (fwrite(&image->file_info.id, sizeof(char), 2, bmp_file) != 2) {
        printf("error on writing file id\n");
        return -1;
    }
    if (fwrite(((char *)&image->file_info)+4, sizeof(bmp_file_info) - 4, 1, bmp_file) != 1) {
        printf("error on writing file information\n");
        return -1;
    }

    // write the file header
    if (fwrite(&image->header, sizeof(bmp3_header), 1, bmp_file) != 1) {
        printf("error on writing file header\n");
        return -1;
    }

    // write the pixel matrix
    line_length = 3 * image->header.width + image->header.width % 4;
    line = malloc(line_length);
    for (i = 0; i < image->header.height; i++) {
        memset(line, 0, line_length);
        memcpy(line, image->matrix[i], 3 * image->header.width);
        if (fwrite(line, line_length, 1, bmp_file) != 1) {
            printf("error on writing line %d\n", i);
            return -1;
        }
    }
    free(line);
    fclose(bmp_file);
    printf("success\n");
    return 0;
}

int create_bmp3(bmp3_image *out_image, int width, int height) {
    int i;

    printf("creating %s... ", out_image->name);

    // initialize the file information
    memset(&out_image->file_info, 0, sizeof(bmp_file_info));
    out_image->file_info.id[0] = 'B';
    out_image->file_info.id[1] = 'M';
    out_image->file_info.file_size = BMP3_IMAGE_OFFSET + (3 * width + width % 4) * height;
    out_image->file_info.offset = BMP3_IMAGE_OFFSET;

    // initialize the file header
    memset(&out_image->header, 0, sizeof(bmp3_header));
    out_image->header.header_size = sizeof(bmp3_header);
    out_image->header.width = width;
    out_image->header.height = height;
    out_image->header.planes = 1;
    out_image->header.bpp = BMP3_BPP;
    out_image->header.image_size = (3 * width + width % 4) * height;

    // set the number of pixels
    out_image->pixel_count = width * height;

    // set the pixel matrix
    alloc_pixel_matrix(out_image);
    for (i = 0; i < out_image->header.height; i++) {
        memset(out_image->matrix[i], 0, 3 * out_image->header.width);
    }

    printf("success\n");
    return 0;
}

void fill_bmp3(bmp3_image *image, enum color color) {
    int row, col;

    for (row = 0; row < image->header.height; row++) {
        for (col = 0; col < image->header.width; col++) {
            image->matrix[row][col] = colors[color];
        }
    }
}
