#ifndef SIMPLE_C_GRAPHICS_ENGINE_FIGURE_H
#define SIMPLE_C_GRAPHICS_ENGINE_FIGURE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Plane.h"
#include "Matrix.h"

typedef struct Figure Figure;
struct Figure {
    int nr_points;
    Vector3Df *points;

    int nr_planes;
    Plane *planes;

    Matrix *model_matrix;
};

void figure_deep_copy(Figure *source, Figure *shallow_copy);

void figure_destroy(Figure *figure);

void figure_print(Figure *figure);

void figure_export(Figure* figure, char *filepath);

Figure* figure_import(char *filepath);

Figure *figure_create_cube();

void figure_apply_transformation(Figure* figure, Matrix *matrix);


#endif //SIMPLE_C_GRAPHICS_ENGINE_FIGURE_H
