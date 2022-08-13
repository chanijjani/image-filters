CC=gcc
PGMS=grayscale threshold sepia sobel sobel5 gaussian_noise3 gaussian_noise5 gaussian_noise7 canny
RTBENCH_PATH=../
BASE_SRC=$(wildcard $(RTBENCH_PATH)/generator/*.c)
BASE_O=$(patsubst %.c,%.o,$(BASE_SRC))
CFLAGS=-O2 -Wall -g -I$(RTBENCH_PATH)/generator -DGCC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-Wl,--no-as-needed -lrt -lm -pthread -ljson-c -Wl,--wrap=malloc -Wl,--wrap=mmap


ifdef CORE
ifeq ($(CORE),CORTEX_A53)
override CFLAGS +=-DAARCH64 -DCORTEX_A53
endif
endif


all: $(PGMS)

obj/common.o:
	$(CC) -c src/common.c -o obj/common.o

obj/filters.o:
	$(CC) -c src/filters.c -o obj/filters.o

grayscale: src/grayscale.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

threshold: src/threshold.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

sepia: src/sepia.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

sobel: src/sobel.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

sobel5: src/sobel5.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

gaussian_noise3: src/gaussian_noise3.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

gaussian_noise5: src/gaussian_noise5.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

gaussian_noise7: src/gaussian_noise7.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

canny: src/canny.o obj/common.o obj/filters.o $(BASE_O)
	$(CC) $(CFLAGS) $(LDFLAGS) $< obj/*.o $(BASE_O) -o $@

clean:
	rm obj/*.o src/*.o $(BASE_O)
