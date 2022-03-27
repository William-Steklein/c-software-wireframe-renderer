#ifndef SIMPLE_C_GRAPHICS_ENGINE_PLANE_H
#define SIMPLE_C_GRAPHICS_ENGINE_PLANE_H

#include <stdlib.h>
#include <string.h>
#include "Vector3Df.h"

typedef struct Plane Plane;
struct Plane {
    int nr_points;
    int *point_indices;
};

void plane_load(Plane *plane, int nr_points, int *point_indices);

void plane_deep_copy(Plane *source, Plane *shallow_copy);

void plane_destroy(Plane *plane);

#endif //SIMPLE_C_GRAPHICS_ENGINE_PLANE_H
