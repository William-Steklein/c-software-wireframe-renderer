#include "Figure.h"

void destroyFigure(Figure *figure) {
    int i;
    for (i = 0; i < figure->nr_points; i++) {
        free(figure->points + i);
    }

    for (i = 0; i < figure->nr_planes; i++) {
        destroyPlane(figure->planes + i);
    }
}

Figure *createCube() {
    // create figure
    Figure *figure = (Figure *) malloc(sizeof(Figure));

    // create points
    figure->nr_points = 8;
    figure->points = (Vector3f *) malloc(sizeof(Vector3f) * figure->nr_points);

    loadVector3f(figure->points + 0, -1, -1, -1, 1);    // 0
    loadVector3f(figure->points + 1, 1, -1, -1, 1);     // 1
    loadVector3f(figure->points + 2, 1, -1, 1, 1);      // 2
    loadVector3f(figure->points + 3, -1, -1, 1, 1);     // 3

    loadVector3f(figure->points + 4, 1, 1, -1, 1);      // 4
    loadVector3f(figure->points + 5, -1, 1, -1, 1);     // 5
    loadVector3f(figure->points + 6, -1, 1, 1, 1);      // 6
    loadVector3f(figure->points + 7, 1, 1, 1, 1);       // 7

    // create planes
    figure->nr_planes = 6;
    figure->planes = (Plane *) malloc(sizeof(Plane) * figure->nr_planes);

    int plane_nr_points = 4;

    // plane 0
    int *point_indices = (int *) malloc(sizeof(int) * plane_nr_points);
    point_indices[0] = 0;
    point_indices[1] = 1;
    point_indices[2] = 2;
    point_indices[3] = 3;

    loadPlane(figure->planes + 0, plane_nr_points, point_indices);

    // plane 1
    point_indices = (int *) malloc(sizeof(int) * plane_nr_points);
    point_indices[0] = 5;
    point_indices[1] = 0;
    point_indices[2] = 3;
    point_indices[3] = 6;

    loadPlane(figure->planes + 1, plane_nr_points, point_indices);

    // plane 2
    point_indices = (int *) malloc(sizeof(int) * plane_nr_points);
    point_indices[0] = 4;
    point_indices[1] = 5;
    point_indices[2] = 6;
    point_indices[3] = 7;

    loadPlane(figure->planes + 2, plane_nr_points, point_indices);

    // plane 3
    point_indices = (int *) malloc(sizeof(int) * plane_nr_points);
    point_indices[0] = 1;
    point_indices[1] = 4;
    point_indices[2] = 7;
    point_indices[3] = 2;

    loadPlane(figure->planes + 3, plane_nr_points, point_indices);

    // plane 4
    point_indices = (int *) malloc(sizeof(int) * plane_nr_points);
    point_indices[0] = 0;
    point_indices[1] = 5;
    point_indices[2] = 4;
    point_indices[3] = 1;

    loadPlane(figure->planes + 4, plane_nr_points, point_indices);

    // plane 5
    point_indices = (int *) malloc(sizeof(int) * plane_nr_points);
    point_indices[0] = 3;
    point_indices[1] = 2;
    point_indices[2] = 7;
    point_indices[3] = 6;

    loadPlane(figure->planes + 5, plane_nr_points, point_indices);


    return figure;
}