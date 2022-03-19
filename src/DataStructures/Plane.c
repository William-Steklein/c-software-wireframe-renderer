#include "Plane.h"

void loadPlane(Plane *plane, int nr_points, int *point_indices) {
    plane->nr_points = nr_points;
    plane->point_indices = point_indices;
}

void destroyPlane(Plane *plane) {
    int i;
    for (i = 0; i < plane->nr_points; i++) {
        free(plane->point_indices + i);
    }

    free(plane);
}