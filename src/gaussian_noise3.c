/**
 * @file gaussian_noise3.c
 * @defgroup gaussian_noise3 Gaussian_noise3
 * @ingroup image-filters
 * @brief Benchmark running gaussian noise filtering with 3x3 kernel size on BMP image.
 * @author Denis Hoornaert <denis.hoornaert@tum.de>
 * @details
 * The original script has been broken down in three components:
 * - init: benchmark_init();
 * - execution: benchmark_execution();
 * - teardown: benchmark_teardown();
 *
 * This allows the benchmark to be run periodically, by re-running only the
 * execution portion.
 *
 * @copyright (C) 2022 Denis Hoornaert <denis.hoornaert@tum.de>
 * SPDX-License-Identifier: MIT
 *
 */

#include "../include/common.h"
#include "../include/filters.h"

// Libraries used by rt-bench
#include "logging.h"
#include "periodic_benchmark.h"

/// Struct storing parsed BMP image as read from the file.
struct bmp_t source;

/// Struct storing the outproduct of the filtering on 'source'.
struct bmp_t target;

/**
 * @brief Reads content of specified BMP file and create a copy.
 * @param[in] parameters_num Number of parameters passed, should be 2.
 * @param[in] parameters The list of passed parameters. First element indicates
 * the BMP file to read and parse.
 * @details
 * The required parameters array is documented in `usage()`, and can be brought
 * up by having "-h" in `parameters`.
 * @returns `0` on success, `-1` on error, setting errno.
 */
int benchmark_init(int parameters_num, void **parameters)
{
	if (parameters_num < 2)
		return -1;

	source = readBMP(parameters[0]);
	grayscale(&source, &source);
	copyBMP(&source, &target);

	return 0;
}

/**
 * @brief Applies sobel filter on the 'source', writing the outcome in 'target'.
 * @param[in] parameters_num Number of passed parameters, ignored.
 * @param[in] parameters The list of passed parameters, ignored.
 * @details
 * This function applies the grayscale filtering on the 'source' image.
 */
void benchmark_execution(int parameters_num, void **parameters)
{
	float conv[3][3] = {{0.05854983f, 0.09653235f, 0.05854983f}, {0.09653235f, 0.15915494f, 0.09653235f}, {0.05854983f, 0.09653235f, 0.05854983f}};
	gaussian_noise(&source, &target, 3, conv);
}

/**
 * @brief Will revert what `benchmark_init()` has done to initialize the
 * benchmark.
 * @param[in] parameters_num should be equal to 2.
 * @param[in] parameters the second option is the BMP image to write to.
 * @details Writes the filtered image as a BMP file and frees the data structs allocated.
 */
void benchmark_teardown(int parameters_num, void **parameters)
{
	writeBMP(parameters[1], target);
        freeBMP(&source);
	freeBMP(&target);
}
