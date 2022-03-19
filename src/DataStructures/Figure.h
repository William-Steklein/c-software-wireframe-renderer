#ifndef C_TEST_FIGURE_H
#define C_TEST_FIGURE_H

#include "Vector3f.h"
#include "Plane.h"
#include <stdlib.h>

typedef struct Figure Figure;
struct Figure {
    int nr_points;
    Vector3f *points;

    int nr_planes;
    Plane *planes;
};

typedef struct Figures Figures;
struct Figures {
    int nr_figures;
    Figure *figures;
};

void destroyFigure(Figure *figure);

Figure *createCube();


#endif //C_TEST_FIGURE_H
