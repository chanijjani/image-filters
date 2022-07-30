#include "../include/common.h"
#include "../include/filters.h"

// Libraries used by rt-bench
#include "logging.h"
#include "periodic_benchmark.h"

struct bmp_t source;

struct bmp_t target;

int benchmark_init(int parameters_num, void **parameters)
{
	if (parameters_num < 2)
		return -1;

	source = readBMP(parameters[0]);
	copyBMP(&source, &target);

	return 0;
}

void benchmark_execution(int parameters_num, void **parameters)
{
	grayscale(&source, &target);
	threshold(&target);
}

void benchmark_teardown(int parameters_num, void **parameters)
{
	writeBMP(parameters[1], target);
        freeBMP(&source);
	freeBMP(&target);
}
