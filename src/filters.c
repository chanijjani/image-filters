/**
 * @file filters.c
 * @ingroup image-filters
 * @brief Collection of the filter's logic.
 *
 * This allows the benchmark to be run periodically, by re-running only the
 * execution portion.
 *
 * Copyright (C) 2022 @author Denis Hoornaert <denis.hoornaert@tum.de>
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/filters.h"

int fpmax(float a, float b) {return (a > b)? a : b;}
int fpmin(float a, float b) {return (a < b)? a : b;}

void threshold(struct bmp_t* img) {
    for (size_t h = 0; h < img->height; h++)
        for (size_t r = 0; r < img->width*img->depth; r++)
            img->data[h][r] = (img->data[h][r] >= 128)? 255 : 0;
}

void grayscale(struct bmp_t* img, struct bmp_t* out) {
    for (size_t h = 0; h < img->height; h++) {
        for (size_t p = 0; p < img->width*img->depth; p+=img->depth) {
            float weighted_sum = ((unsigned char)img->data[h][p+2]*0.2989f) + ((unsigned char)img->data[h][p+1]*0.5870f) + ((unsigned char)img->data[h][p+0]*0.1140f);
            char gray = (weighted_sum >= 255)? 255 : weighted_sum;
            out->data[h][p+0] = gray;
            out->data[h][p+1] = gray;
            out->data[h][p+2] = gray;
        }
    }
}

void sepia(struct bmp_t* img, struct bmp_t* out) {
    for (size_t h = 0; h < img->height; h++) {
        for (size_t p = 0; p < img->width*img->depth; p+=img->depth) {
            float r = (unsigned char)img->data[h][p+2];
            float g = (unsigned char)img->data[h][p+1];
            float b = (unsigned char)img->data[h][p+0];
            float tr = (r*0.393f) + (g*0.769f) + (b*0.189f);
            float tg = (r*0.349f) + (g*0.686f) + (b*0.168f);
            float tb = (r*0.272f) + (g*0.534f) + (b*0.131f);
            out->data[h][p+2] = (tr >= 255)? 255 : ((unsigned)tr)&0x000000ff;
            out->data[h][p+1] = (tg >= 255)? 255 : ((unsigned)tg)&0x000000ff;
            out->data[h][p+0] = (tb >= 255)? 255 : ((unsigned)tb)&0x000000ff;
        }
    }
}

void sobel(struct bmp_t* img, struct bmp_t* out) {
    int kh[3][3] = {{-1, -2, -1},  {0, 0, 0}, { 1, 2, 1}};
    int kv[3][3] = {{-1,  0,  1}, {-2, 0, 2}, {-1, 0, 1}};
    for (size_t h = 1; h < img->height-1; h++) {
        for (size_t p = img->depth; p < (img->width-1)*img->depth; p+=img->depth) {
            int gx = 0;
            int gy = 0;
            for (size_t i = 0; i < 3; i++) {
                for (size_t j = 0; j < 3; j++) {
                    gx += img->data[h+(i-1)][p+((j-1)*img->depth)]*kh[i][j];
                    gy += img->data[h+(i-1)][p+((j-1)*img->depth)]*kv[i][j];
                }
            }
            char color = fpmin(fpmax(sqrt(pow(gx, 2)+pow(gy, 2)), 0), 255);
            out->data[h][p+2] = color;
            out->data[h][p+1] = color;
            out->data[h][p+0] = color;
        }
    }
}

void sobel5(struct bmp_t* img, struct bmp_t* out) {
    int kh[5][5] = {{ 5,  8, 10,  8,  5}, { 4, 10, 20, 10,  4}, { 0,  0,  0,  0,  0}, { -4, -10, -20, -10, -4}, {-5, -8, -10, -8, -5}};
    int kv[5][5] = {{ 5,  4,  0, -4, -5}, { 8, 10,  0, -10, -8}, {10, 20,  0, -20, -10}, { 8, 10,  0, -10, -8}, { 5,  4,  0, -4, -5}};
    for (size_t h = 2; h < img->height-2; h++) {
        for (size_t p = img->depth*2; p < (img->width-2)*img->depth; p+=img->depth) {
	    int gx = 0;
            int gy = 0;
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    gx += img->data[h+(i-2)][p+((j-2)*img->depth)]*kh[i][j];
                    gy += img->data[h+(i-2)][p+((j-2)*img->depth)]*kv[i][j];
                }
            }
            char color = fpmin(fpmax(sqrt(pow(gx, 2)+pow(gy, 2)), 0), 255);
            out->data[h][p+2] = color;
            out->data[h][p+1] = color;
            out->data[h][p+0] = color;
        }
    }
}

void gaussian_noise(struct bmp_t* img, struct bmp_t* out, unsigned size, float conv[size][size]) {
    unsigned half_size = size/2;
    for (size_t h = half_size; h < img->height-half_size; h++) {
        for (size_t r = img->depth*half_size; r < (img->width-half_size)*img->depth; r++) {
            int res = 0;
            for (size_t i = 0; i < size; i++) {
                for (size_t j = 0; j < size; j++) {
                    res += img->data[h+(i-half_size)][r+((j-half_size)*img->depth)]*conv[i][j];
                }
            }
            out->data[h][r] = fpmin(fpmax(res, 0), 255);
        }
    }
}
