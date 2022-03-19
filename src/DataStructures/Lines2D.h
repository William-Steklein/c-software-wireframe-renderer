#ifndef C_TEST_LINES2D_H
#define C_TEST_LINES2D_H

#include "Line2D.h"

typedef struct Lines2D Lines2D;
struct Lines2D {
    int nr_points;
    Vector2f *points;

    int nr_lines;
    Line2D *lines;
};

void loadLines2D(Lines2D *lines2d, int nr_lines, Line2D *lines) {
    lines2d->nr_lines = nr_lines;
    lines2d->lines = lines;
}

Lines2D *createRectangle() {
    Lines2D *lines2d = (Lines2D *) malloc(sizeof(Lines2D));

    // points
    lines2d->nr_points = 4;
    lines2d->points = (Vector2f *) malloc(sizeof(Vector2f) * lines2d->nr_points);

    loadVector2f(lines2d->points + 0, -1, -1);
    loadVector2f(lines2d->points + 1, 1, -1);
    loadVector2f(lines2d->points + 2, 1, 1);
    loadVector2f(lines2d->points + 3, -1, 1);

    // lines
    lines2d->nr_lines = 4;
    lines2d->lines = (Line2D *) malloc(sizeof(Line2D) * lines2d->nr_lines);

    loadLine2D(lines2d->lines + 0, 0, 1);
    loadLine2D(lines2d->lines + 1, 1, 2);
    loadLine2D(lines2d->lines + 2, 2, 3);
    loadLine2D(lines2d->lines + 3, 3, 0);

    return lines2d;
}

#endif //C_TEST_LINES2D_H
