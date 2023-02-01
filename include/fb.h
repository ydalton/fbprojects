#ifndef FB_H_
#define FB_H_

#include <stdio.h>

#define PATH_FB "/dev/fb0"

typedef unsigned char byte;

void fbDrawPixel(FILE *fb, byte r, byte g, byte b);

#endif
