#include "Figure.h"

void destroyFigure(Figure *figure) {
    int i;
    free(figure->points);

    for (i = 0; i < figure->nr_planes; i++) {
        destroyPlane(figure->planes + i);
    }
    free(figure->planes);
}

void printFigure(Figure *figure) {
    printf("Figure:\nnr_points: %d\nnr_planes: %d\n", figure->nr_points, figure->nr_planes);
}

void applyTransformation(Figure *figure, Matrix *matrix) {
    int i;
    for (i = 0; i < figure->nr_points; i++) {
        vector3frefDotMatrix(figure->points + i, matrix);
    }
}

void exportFigure(Figure *figure, char *filepath) {
    FILE *f = fopen(filepath, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "o Figure\n");

    int point_nr;
    for (point_nr = 0; point_nr < figure->nr_points; point_nr++) {
        fprintf(f, "v %f %f %f\n",
                figure->points[point_nr].x,
                figure->points[point_nr].y,
                figure->points[point_nr].z
        );
    }

    int face_nr;
    for (face_nr = 0; face_nr < figure->nr_planes; face_nr++) {
        // todo: rewrite for different kind of faces
        fprintf(f, "f %d %d %d %d\n",
                figure->planes[face_nr].point_indices[0] + 1,
                figure->planes[face_nr].point_indices[1] + 1,
                figure->planes[face_nr].point_indices[2] + 1,
                figure->planes[face_nr].point_indices[3] + 1
        );
    }

    fclose(f);
}

Figure *importFigure(char *filepath) {
    Figure *figure = (Figure *) malloc(sizeof(Figure));

    // max line length
    int bufferLength = 255;
    char buffer[bufferLength];

    FILE *f = fopen(filepath, "r");

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    figure->nr_points = 0;
    figure->nr_planes = 0;

    // count all vertices and faces
    while (fgets(buffer, bufferLength, f)) {
        if (buffer[0] == 'v' && buffer[1] == ' ') {
            figure->nr_points++;
        }

        if (buffer[0] == 'f' && buffer[1] == ' ') {
            figure->nr_planes++;
        }
    }

    fclose(f);

    figure->points = (Vector3f *) malloc(sizeof(Vector3f) * figure->nr_points);
    figure->planes = (Plane *) malloc(sizeof(Plane) * figure->nr_planes);

    f = fopen(filepath, "r");

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    int current_vertex_count = 0;
    int vertex_component = 0;
    int current_face_count = 0;

    while (fgets(buffer, bufferLength, f)) {
        if (buffer[0] == 'v' && buffer[1] == ' ') {
            vertex_component = 0;

            char *split_buffer;
            split_buffer = strtok(buffer, " /\n\r");
            while (split_buffer != NULL) {
                if (split_buffer[0] == 'v') {
                    split_buffer = strtok(NULL, " /\n\r");
                    continue;
                }

                if (vertex_component == 0) {
                    figure->points[current_vertex_count].x = strtof(split_buffer, NULL);
                } else if (vertex_component == 1) {
                    figure->points[current_vertex_count].y = strtof(split_buffer, NULL);
                } else if (vertex_component == 2) {
                    figure->points[current_vertex_count].z = strtof(split_buffer, NULL);
                    figure->points[current_vertex_count].h = 1;
                }

                vertex_component++;

                split_buffer = strtok(NULL, " /\n\r");
            }

            current_vertex_count++;
        }

        if (buffer[0] == 'f' && buffer[1] == ' ') {
            char *buffer_cpy = (char *) malloc(sizeof(char) * bufferLength);
            memcpy(buffer_cpy, buffer, sizeof(char) * bufferLength);

            // count number of vertices in face
            int fv_count = 0;

            char *split_buffer;
            split_buffer = strtok(buffer_cpy, " \n\r");
            while (split_buffer != NULL) {
                if (split_buffer[0] == 'f') {
                    split_buffer = strtok(NULL, " \n\r");
                    continue;
                }

                fv_count++;
                split_buffer = strtok(NULL, " \n\r");
            }

            memcpy(buffer_cpy, buffer, sizeof(char) * bufferLength);

            figure->planes[current_face_count].nr_points = fv_count;
            figure->planes[current_face_count].point_indices = (int *) malloc(sizeof(int) * fv_count);

            int face_point_index = 0;

            split_buffer = strtok(buffer_cpy, " \n\r");
            while (split_buffer != NULL) {
                if (split_buffer[0] == 'f') {
                    split_buffer = strtok(NULL, " \n\r");
                    continue;
                }
                char *number = (char *) calloc( bufferLength, sizeof(char));

                int i;
                for (i = 0; i < bufferLength; i++) {
                    if (split_buffer[i] != '/') {
                        number[i] = split_buffer[i];
                    } else {
                        break;
                    }
                }

                figure->planes[current_face_count].point_indices[face_point_index] = atoi(number) - 1;

                face_point_index++;

                split_buffer = strtok(NULL, " \n\r");
            }
            current_face_count++;
        }
    }

    fclose(f);

    return figure;
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