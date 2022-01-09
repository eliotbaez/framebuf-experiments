#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

struct Pixel {
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t _unused;
};

typedef struct Pixel pixel_t;

/* some conversion functions in case I need them */
pixel_t RGBtoPixel(uint8_t r, uint8_t g, uint8_t b);

#endif /* PIXEL_H */
