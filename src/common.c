#include "../include/common.h"

struct bmp_t readBMP(const char* file) {
    FILE *fp;
    struct bmp_t img;

    fp = fopen(file, "rb");
    img.header = (uint8_t*)malloc(54*sizeof(uint8_t));
    fread(img.header, sizeof(uint8_t), 54, fp);

    img.file_size = img.header[2] | (img.header[3] << 8) | (img.header[4] << 8) | (img.header[5] << 8);
    img.data_offset = img.header[10] | (img.header[11] << 8) | (img.header[12] << 8) | (img.header[13] << 8);
    img.width = img.header[18] | (img.header[19] << 8) | (img.header[20] << 8) | (img.header[21] << 8);
    img.height = img.header[22] | (img.header[23] << 8) | (img.header[24] << 8) | (img.header[25] << 8);
    img.depth = (img.header[28] | (img.header[29] << 8) | (img.header[30] << 8) | (img.header[31] << 8))>>3;

    img.data = (uint8_t**)malloc(img.height*sizeof(uint8_t*));
    for (size_t h = 0; h < img.height; h++) {
        img.data[h] = (uint8_t*)malloc(img.width*img.depth*sizeof(uint8_t));
        fread(img.data[h], sizeof(uint8_t), img.width*img.depth, fp);
    }

    fclose(fp);

    return img;
}

void copyBMP(struct bmp_t* img, struct bmp_t* out) {
    out->file_size = img->file_size;
    out->data_offset = img->data_offset;
    out->width = img->width;
    out->height = img->height;
    out->depth = img->depth;
    // Handling header
    out->header = (uint8_t*)malloc(54*sizeof(uint8_t));
    for (size_t e = 0; e < 54; e++)
        out->header[e] = img->header[e];
    // Handling data
    out->data = (uint8_t**)malloc(img->height*sizeof(uint8_t*));
    for (size_t h = 0; h < img->height; h++)
        out->data[h] = (uint8_t*)malloc(img->width*img->depth*sizeof(uint8_t));
    for (size_t h = 0; h < img->height; h++) // TODO: memcpy
        for (size_t r = 0; r < img->width*img->depth; r++)
            out->data[h][r] = img->data[h][r];
}

void writeBMP(const char* file, struct bmp_t img) {
    FILE *fp;

    fp = fopen(file, "wb");
    fwrite(img.header, sizeof(uint8_t), 54, fp);

    for (size_t h = 0; h < img.height; h++)
        fwrite(img.data[h], sizeof(uint8_t), img.width*img.depth, fp);

    fclose(fp);
}

void freeBMP(struct bmp_t* img) {
    for (size_t h = 0; h < img->height; h++) {
        free(img->data[h]);
        img->data[h] = NULL;
    }
    free(img->data);
    img->data = NULL;
}

