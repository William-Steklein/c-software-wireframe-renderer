#include "Plane.h"

void plane_load(Plane *plane, int nr_points, int *point_indices) {
    plane->nr_points = nr_points;
    plane->point_indices = point_indices;
}

void plane_deep_copy(Plane *source, Plane *shallow_copy) {
    shallow_copy->nr_points = source->nr_points;

    shallow_copy->point_indices = (int *) malloc(sizeof(int));
    memcpy(shallow_copy->point_indices, source->point_indices, sizeof(int) * source->nr_points);
}

void plane_destroy(Plane *plane) {
    free(plane->point_indices);
}
