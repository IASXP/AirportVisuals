// drawing.h
#ifndef DRAWING_H
#define DRAWING_H

#include <cairo.h>

void drawMapRWY(cairo_t *cr, double x, double y, const char *apt, int pixelsPerNM);

#endif // DRAWING_H
