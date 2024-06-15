#include "common.h"
#include <X11/extensions/XInput2.h>
#include <X11/extensions/Xrandr.h>

/* This file provides a map which assumes the entire
   rectangular display area is viewable. */

static int width, height;

static Pair* xvals;
static Pair* yvals;

void map_init(Display* dpy)
{
	int screen = DefaultScreen(dpy);
	width = DisplayWidth(dpy, screen);
	height = DisplayHeight(dpy, screen);

	Window win = DefaultRootWindow(dpy);
	XRRScreenResources* xrrr = XRRGetScreenResources(dpy, win);
	XRRCrtcInfo* xrrci;
	int ncrtc = xrrr->ncrtc;

	xvals = malloc(width * sizeof(Pair));
	for (int x = 0; x < width; x++) {
		xvals[x] = (Pair){ .min = height, .max = 0 };
		// check y wrap values at each x level for each monitor
		for (int i = 0; i < ncrtc; i++) {
			xrrci = XRRGetCrtcInfo(dpy, xrrr, xrrr->crtcs[i]);
			int h = xrrci->x + xrrci->height;
			if (xvals[x].min > xrrci->x)
				xvals[x].min = xrrci->x;
			if (xvals[x].max < h)
				xvals[x].max = h;

			XRRFreeCrtcInfo(xrrci);
		}
	}

	yvals = malloc(height * sizeof(Pair));
	for (int y = 0; y < height; y++) {
		yvals[y] = (Pair){ .min = width, .max = 0 };
		// check x wrap values at each y level for each monitor
		for (int i = 0; i < ncrtc; i++) {
			xrrci = XRRGetCrtcInfo(dpy, xrrr, xrrr->crtcs[i]);
			int w = xrrci->y + xrrci->width;
			if (yvals[y].min > xrrci->y)
				yvals[y].min = xrrci->y;
			if (yvals[y].max < w)
				yvals[y].max = w;
			//
			XRRFreeCrtcInfo(xrrci);
		}
	}
}

void map(int* x, int* y)
{
	WRAP(x, 0, width - 2);
	WRAP(x, width - 1, 1);
	WRAP(y, 0, height - 2);
	WRAP(y, height - 1, 1);
}
