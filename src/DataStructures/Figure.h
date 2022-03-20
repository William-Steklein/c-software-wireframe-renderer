#ifndef C_TEST_FIGURE_H
#define C_TEST_FIGURE_H

#include "Matrix.h"
#include "Plane.h"
#include <stdlib.h>

typedef struct Figure Figure;
struct Figure {
    int nr_points;
    Vector3f *points;

    int nr_planes;
    Plane *planes;
};

void destroyFigure(Figure *figure);

void printFigure(Figure *figure);

void applyTransformation(Figure* figure, Matrix *matrix);

void exportFigure(Figure* figure, char *filepath);

Figure *createCube();


#endif //C_TEST_FIGURE_H
