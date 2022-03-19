#ifndef C_TEST_PLANE_H
#define C_TEST_PLANE_H

#include "Vector3f.h"

typedef struct Plane Plane;
struct Plane {
    int nr_points;
    int* point_indices;
};

void loadPlane(Plane* plane, int nr_points, int* point_indices) {
    plane->nr_points = nr_points;
    plane->point_indices = point_indices;
}

#endif //C_TEST_PLANE_H
