RTBENCH_PATH=..
include $(RTBENCH_PATH)/generator/Makefile

PGMS=grayscale threshold sepia sobel sobel5 gaussian_noise3 gaussian_noise5 gaussian_noise7 canny
BASE_SRC=$(wildcard $(RTBENCH_PATH)/generator/*.c)
BASE_O=$(patsubst %.c,%.o,$(BASE_SRC))
override CFLAGS+=-O2 -Wall -g -I$(RTBENCH_PATH)/generator -DGCC
CXXFLAGS=$(CFLAGS)
override LDFLAGS+=-Wl,--no-as-needed

all: $(PGMS)

obj/common.o:
	$(CROSS_COMPILE)$(CC) -c src/common.c -o obj/common.o

obj/filters.o:
	$(CROSS_COMPILE)$(CC) -c src/filters.c -o obj/filters.o

grayscale: src/grayscale.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

threshold: src/threshold.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

sepia: src/sepia.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

sobel: src/sobel.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

sobel5: src/sobel5.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

gaussian_noise3: src/gaussian_noise3.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

gaussian_noise5: src/gaussian_noise5.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

gaussian_noise7: src/gaussian_noise7.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

canny: src/canny.o obj/common.o obj/filters.o $(BASE_O)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $< obj/*.o $(BASE_O) -o $@ $(LDFLAGS)

clean:
	rm -f obj/*.o src/*.o $(BASE_O)
