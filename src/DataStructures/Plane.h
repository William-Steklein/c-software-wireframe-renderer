#ifndef C_TEST_PLANE_H
#define C_TEST_PLANE_H

#include <stdlib.h>
#include "Vector3f.h"

typedef struct Plane Plane;
struct Plane {
    int nr_points;
    int *point_indices;
};

void loadPlane(Plane *plane, int nr_points, int *point_indices);

void destroyPlane(Plane *plane);

#endif //C_TEST_PLANE_H
