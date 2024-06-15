#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/X.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/Xrandr.h>

#define WRAP(_var, _from, _to)                                                 \
	do {                                                                         \
		if (*_var == (_from)) {                                                    \
			*_var = (_to);                                                           \
			return;                                                                  \
		}                                                                          \
	} while (0)

typedef struct
{
	void (*map_init)(Display* dpy);
	void (*map)(int* x, int* y);
} Map;

typedef struct
{
	int min;
	int max;
} Pair;

void map_init(Display* dpy);
void map(int* x, int* y);
