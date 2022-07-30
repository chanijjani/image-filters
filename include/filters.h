#include "../include/common.h"

#ifndef FILTERS_H
#define FILTERS_H

int fpmax(float a, float b);

int fpmin(float a, float b);

void threshold(struct bmp_t* img);

void grayscale(struct bmp_t* img, struct bmp_t* out);

void sepia(struct bmp_t* img, struct bmp_t* out);

void sobel(struct bmp_t* img, struct bmp_t* out);

#endif /* FILTERS_H */
