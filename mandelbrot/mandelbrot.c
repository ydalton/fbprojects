#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fb.h"

/* screen width and height, change these to fit your screen size */
#define WIDTH 1920
#define HEIGHT 1080

#define MAX_ITER 255

const double ratio = (double) WIDTH / HEIGHT;

const double cre = -0.5;
const double cim = 0;
const double diam = 2.5;

const double minr = cre - (diam * 0.5 * ratio);
const double mini = cim - diam * 0.5;
const double maxr = cre + (diam * 0.5 * ratio);
const double maxi = cim + diam * 0.5;

const double stepr = (maxr - minr) / WIDTH;
const double stepi = (maxi - mini) / HEIGHT;

/* the actual brains of the Mandelbrot set */
int iterate(double x, double y, uint16_t max_iter) {
    int iter;
    double r = x;
    double i = y;
    for (iter = 0; iter < max_iter; ++iter) {
        double r2 = r*r, i2 = i*i;
        if(r2+i2 >= 4.0) break;
        double ri = r*i;
        i = ri+ri + y;
        r = r2-i2 + x;
    }
    return iter;
}

int main() {
    FILE *fb = fopen(PATH_FB, "w");
    if(fb == NULL) {
        perror("Could not open framebuffer!");
        exit(1);
    }
    uint16_t x, y;
    uint8_t c;
    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            c = iterate(minr + x * stepr, mini + y * stepi, MAX_ITER); 
            fbDrawPixel(fb, c, c, c);
        }
    }
    fclose(fb);
}
