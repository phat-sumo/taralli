#include "common.h"

/* This file provides a map for a machine with
   the following screen layout:

   todo: make some sick ascii art

1920x1080 - 2560x1440 - 1920x1080

*/

void map_init(Display *dpy) {
}

void map(int *x, int *y) {
    int w = 2560 + 1920*2;
    WRAP(x, 0, w-2);
    WRAP(x, w-1, 1);

    int h = ((*x < 1920) || (*x > 1920+2560)) ? 1080 : 1440;
    WRAP(y, 0, h-2);
    WRAP(y, h-1, 1);
}
