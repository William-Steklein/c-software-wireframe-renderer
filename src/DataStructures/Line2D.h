#ifndef SIMPLE_C_GRAPHICS_ENGINE_LINE2D_H
#define SIMPLE_C_GRAPHICS_ENGINE_LINE2D_H

#include <stdlib.h>
#include <stdio.h>
#include "Vector2Df.h"

typedef struct Line2D Line2D;
struct Line2D {
    int p1_index;
    int p2_index;
};

void line2d_load(Line2D *line2d, int p1_index, int p2_index);

void line2d_print(Line2D* line2d, Vector2Df *points);

typedef struct Lines2D Lines2D;
struct Lines2D {
    int nr_points;
    Vector2Df *points;

    int nr_lines;
    Line2D *lines;
};

void lines2d_load(Lines2D *lines2d, int nr_lines, Line2D *lines);

void lines2d_print(Lines2D* lines2d);

void lines2d_destroy(Lines2D *lines2d);

Lines2D *lines2d_create_rectangle();

#endif //SIMPLE_C_GRAPHICS_ENGINE_LINE2D_H
