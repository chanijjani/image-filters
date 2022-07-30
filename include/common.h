#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>


#ifndef COMMON_H
#define COMMON_H

struct bmp_t {
    uint32_t file_size;
    uint32_t data_offset;
    uint32_t width;
    uint32_t height;
    uint16_t depth;
    uint8_t* header;
    uint8_t** data;
};

struct bmp_t readBMP(const char* file);

void copyBMP(struct bmp_t* img, struct bmp_t* out);

void writeBMP(const char* file, struct bmp_t img);

void freeBMP(struct bmp_t* img);

#endif /* COMMON_H */
