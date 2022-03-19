#ifndef C_TEST_LINE2D_H
#define C_TEST_LINE2D_H

#include <stdlib.h>
#include "Vector2f.h"

typedef struct Line2D Line2D;
struct Line2D {
    int p1_index;
    int p2_index;
};

void loadLine2D(Line2D *line2d, int p1_index, int p2_index) {
    line2d->p1_index = p1_index;
    line2d->p2_index = p2_index;
}

void printLine2D(Line2D* line2d, Vector2f *points) {
    printf("|");
    printVector2f(points + line2d->p1_index);
    printf(", ");
    printVector2f(points + line2d->p2_index);
    printf("|\n");
}

#endif //C_TEST_LINE2D_H
