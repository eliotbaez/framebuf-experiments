#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include "stdlib.h"
#include "pixel.h"

struct Screen {
	unsigned int width;
	unsigned int height;
	size_t size;
	pixel_t *pixels;
	/* pointer array for pixels, accessible by pixelAt[x][y] */
	pixel_t **pixelAt;
};

typedef struct Screen screen_t;

/* constructor and destructor */
screen_t *initScreen(unsigned int width, unsigned int height);
int endScreen(screen_t *screen);

/* DOES NOT CHECK FOR NULL POINTERS. */
size_t fDrawScreen(FILE *framebuffer, screen_t *scr);

/* some useful manipulation functions */
int fillScreen(screen_t *scr, pixel_t pxl);
int fillRectangle( screen_t *scr,
		unsigned int topleft_x,
		unsigned int topleft_y,
		unsigned int width,
		unsigned int height );
int drawLine( screen_t *scr,
		unsigned int x1,
		unsigned int y1,
		unsigned int x2,
		unsigned int y2 );

/* you'll probably never use this one, but declare it just in case */
int setPixel( screen_t *scr,
		unsigned int x,
		unsigned int y,
		pixel_t pxl );

#endif /* SCREEN_H */
