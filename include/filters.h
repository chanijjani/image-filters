/**
 * @file filters.h
 * @ingroup image-filters
 * @brief Collection of the filters functions.
 * @author Denis Hoornaert
 *
 * Copyright (C) 2021 - 2022, Denis Hoornaert <denis.hoornaert@tum.de>.
 * SPDX-License-Identifier: MIT
*/

#ifndef FILTERS_H
#define FILTERS_H

#include "../include/common.h"

/** @brief Function returning as int the maximal value between two floats.
 * @param[in] a First float to compare.
 * @param[in] b Second float to compare.
 * @return Returns an integer version of the biggest float operand.
 */
int fpmax(float a, float b);

/** @brief Function returning as int the minimal value between two floats.
 * @param[in] a First float to compare.
 * @param[in] b Second float to compare.
 * @return Returns an integer version of the smallest float operand.
 */
int fpmin(float a, float b);

/** @brief Function applying sequentially a grayscale and a threshold filtering
 * on the image given in parameter.
 * @param[inout] img Pointer of `bmp_t` on which the filter will be applied.
 */
void threshold(struct bmp_t* img);

/** @brief Function applying a grayscale filter on the image given in paramter.
 * @param[in] img Input image from which the data is read.
 * @param[in] out Output image in which the filtered image is stored.
 */
void grayscale(struct bmp_t* img, struct bmp_t* out);

/** @brief Function applying a sepia filter on the image given in paramter.
 * @param[in] img Input image from which the data is read.
 * @param[in] out Output image in which the filtered image is stored.
 */
void sepia(struct bmp_t* img, struct bmp_t* out);

/** @brief Function applying a sobel filter on the image given in paramter.
 * @param[in] img Input image from which the data is read.
 * @param[in] out Output image in which the filtered image is stored.
 */
void sobel(struct bmp_t* img, struct bmp_t* out);

#endif /* FILTERS_H */
