/*
 * main.c
 * by Eliot Baez
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "pixel.h"
#include "screen.h"
#define PIXELS (1080 * 1920)

int main(int argc, char **argv) {
	pixel_t pixel;
	screen_t *screen;
	int i;
	FILE *fb;

	if (argc != 4) {
		fprintf(stderr, "%s takes exactly 3 arguments.\n", argv[0]);
		return EXIT_FAILURE;
	}

	fb = fopen("/dev/fb0", "wb");
	if (fb == NULL) {
		perror("Error opening /dev/fb0");
		return EXIT_FAILURE;
	}

	pixel.r = strtol(argv[1], NULL, 0);
	pixel.g = strtol(argv[2], NULL, 0);
	pixel.b = strtol(argv[3], NULL, 0);
	pixel._unused = 0;

	screen = initScreen(1920, 1080);

	fillScreen(screen, pixel);
	pixel.r = 0xff - pixel.r;
	pixel.g = 0xff - pixel.g;
	pixel.b = 0xff - pixel.b;
	for (i = 0; i < 1080; ++i) {
		screen->pixelAt[i][i] = pixel;
		screen->pixelAt[i][1080 - i] = pixel;
	}
	
	fDrawScreen(fb, screen);
	
	fclose(fb);
	endScreen(screen);

	return 0;
}
