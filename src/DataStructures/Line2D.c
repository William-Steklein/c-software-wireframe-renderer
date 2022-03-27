#include "Line2D.h"

void line2d_load(Line2D *line2d, int p1_index, int p2_index) {
    line2d->p1_index = p1_index;
    line2d->p2_index = p2_index;
}

void lines2d_load(Lines2D *lines2d, int nr_lines, Line2D *lines) {
    lines2d->nr_lines = nr_lines;
    lines2d->lines = lines;
}

void line2d_print(Line2D* line2d, Vector2Df *points) {
    printf("|");
    vector2df_print(points + line2d->p1_index);
    printf(", ");
    vector2df_print(points + line2d->p2_index);
    printf("|\n");
}

void lines2d_print(Lines2D* lines2d) {
    printf("nr_points: %d, nr_lines: %d\n", lines2d->nr_points, lines2d->nr_lines);
    int line;
    for (line = 0; line < lines2d->nr_lines; line++) {
        line2d_print(lines2d->lines + line, lines2d->points);
    }
}

void lines2d_destroy(Lines2D *lines2d) {
    free(lines2d->points);
    free(lines2d->lines);

    free(lines2d);
}

Lines2D *lines2d_create_rectangle() {
    Lines2D *lines2d = (Lines2D *) malloc(sizeof(Lines2D));

    // points
    lines2d->nr_points = 4;
    lines2d->points = (Vector2Df *) malloc(sizeof(Vector2Df) * lines2d->nr_points);

    vector2df_load(lines2d->points + 0, -1, -1);
    vector2df_load(lines2d->points + 1, 1, -1);
    vector2df_load(lines2d->points + 2, 1, 1);
    vector2df_load(lines2d->points + 3, -1, 1);

    // lines
    lines2d->nr_lines = 4;
    lines2d->lines = (Line2D *) malloc(sizeof(Line2D) * lines2d->nr_lines);

    line2d_load(lines2d->lines + 0, 0, 1);
    line2d_load(lines2d->lines + 1, 1, 2);
    line2d_load(lines2d->lines + 2, 2, 3);
    line2d_load(lines2d->lines + 3, 3, 0);

    return lines2d;
}