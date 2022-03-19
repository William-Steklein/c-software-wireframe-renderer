#include "Line2D.h"

void loadLine2D(Line2D *line2d, int p1_index, int p2_index) {
    line2d->p1_index = p1_index;
    line2d->p2_index = p2_index;
}

void printLine2D(Line2D* line2d, Vector2f *points) {
    printf("|");
    printVector2f(points + line2d->p1_index);
    printf(", ");
    printVector2f(points + line2d->p2_index);
    printf("|\n");
}

void loadLines2D(Lines2D *lines2d, int nr_lines, Line2D *lines) {
    lines2d->nr_lines = nr_lines;
    lines2d->lines = lines;
}

void destroyLines2D(Lines2D *lines2d) {
    free(lines2d->points);
    free(lines2d->lines);

    free(lines2d);
}

Lines2D *createRectangle() {
    Lines2D *lines2d = (Lines2D *) malloc(sizeof(Lines2D));

    // points
    lines2d->nr_points = 4;
    lines2d->points = (Vector2f *) malloc(sizeof(Vector2f) * lines2d->nr_points);

    loadVector2f(lines2d->points + 0, -1, -1);
    loadVector2f(lines2d->points + 1, 1, -1);
    loadVector2f(lines2d->points + 2, 1, 1);
    loadVector2f(lines2d->points + 3, -1, 1);

    // lines
    lines2d->nr_lines = 4;
    lines2d->lines = (Line2D *) malloc(sizeof(Line2D) * lines2d->nr_lines);

    loadLine2D(lines2d->lines + 0, 0, 1);
    loadLine2D(lines2d->lines + 1, 1, 2);
    loadLine2D(lines2d->lines + 2, 2, 3);
    loadLine2D(lines2d->lines + 3, 3, 0);

    return lines2d;
}