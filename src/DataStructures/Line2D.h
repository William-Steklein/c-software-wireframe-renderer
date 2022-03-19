#ifndef C_TEST_LINE2D_H
#define C_TEST_LINE2D_H

#include <stdlib.h>
#include <stdio.h>
#include "Vector2f.h"

typedef struct Line2D Line2D;
struct Line2D {
    int p1_index;
    int p2_index;
};

typedef struct Lines2D Lines2D;
struct Lines2D {
    int nr_points;
    Vector2f *points;

    int nr_lines;
    Line2D *lines;
};

void loadLine2D(Line2D *line2d, int p1_index, int p2_index);

void printLine2D(Line2D* line2d, Vector2f *points);

void loadLines2D(Lines2D *lines2d, int nr_lines, Line2D *lines);

void destroyLines2D(Lines2D *lines2d);

Lines2D *createRectangle();

#endif //C_TEST_LINE2D_H
