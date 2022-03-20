#include "Plane.h"

void loadPlane(Plane *plane, int nr_points, int *point_indices) {
    plane->nr_points = nr_points;
    plane->point_indices = point_indices;
}

void destroyPlane(Plane *plane) {
    free(plane->point_indices);
}