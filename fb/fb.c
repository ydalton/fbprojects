#include "fb.h"

void fbDrawPixel(FILE *fb, byte r, byte g, byte b) {
    fputc(b, fb);
    fputc(g, fb);
    fputc(r, fb);
    fputc(0x00, fb);
}
