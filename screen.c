#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "pixel.h"

screen_t *initScreen(unsigned int width, unsigned int height) {
	screen_t *screen;
	size_t i, j;

	screen = calloc(sizeof(screen_t), 1);
	if (screen == NULL)
		return NULL;

	screen->width = width;
	screen->height = height;
	screen->size = width * height;
	 
	screen->pixels = calloc(sizeof(pixel_t), screen->size);
	screen->pixelAt = calloc(sizeof(pixel_t *), screen->height);
	if (screen->pixels == NULL || screen->pixelAt == NULL) {
		free(screen->pixels);
		free(screen->pixelAt);
		free(screen);
		return NULL;
	}
	
	for (i = 0, j = 0; i < screen->height; ++i) {
		screen->pixelAt[i] = screen->pixels + j;
		j += screen->width;
	}

	return screen;
}

int endScreen(screen_t *scr) {
	if (scr == NULL)
		/* not necessarily bad, just unexpected */
		return 1;
	free(scr->pixels);
	free(scr->pixelAt);
	free(scr);
	return 0;
}

size_t fDrawScreen(FILE *framebuffer, screen_t *scr) {
	size_t written;
	fseek(framebuffer, 0, SEEK_SET);
	written = fwrite(scr->pixels, sizeof(pixel_t), scr->size, framebuffer);
	fflush(framebuffer);
	return written;
}

int fillScreen(screen_t *scr, pixel_t pxl) {
	size_t i;
	if (scr == NULL)
		return 0;

	if (sizeof(unsigned long) == 2 * sizeof(pixel_t)) {
		/* special case if word size can accommodate two pixels at once */
		size_t words;
		pixel_t twopixels[2] = {pxl, pxl};
		unsigned long *wordarray = (unsigned long *)scr->pixels;

		words = scr->size / 2;
		for (i = 0; i < words; ++i)
			wordarray[i] = *((unsigned long *)twopixels);
		if (scr->size % 2 == 1)
			scr->pixels[scr->size - 1] = pxl;
	} else {
		/* just fill pixel by pixel otherwise */
		for (i = 0; i < scr->size; ++i)
			scr->pixels[i] = pxl;
	}
	return scr->size;
}


