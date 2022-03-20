#include "engine.h"

void run() {
    // SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Simple C Graphics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          window_width,
                                          window_height, SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Load figures
    engine.nr_figures = 1;
    engine.figures = (Figure *) malloc(sizeof(Figure) * engine.nr_figures);
    engine.transformed_figures = (Figure *) malloc(sizeof(Figure) * engine.nr_figures);

    engine.figures = createCube();
    engine.figure_lines = (Lines2D *) malloc(sizeof(Lines2D) * engine.nr_figures);
    memcpy(engine.transformed_figures, engine.figures, sizeof(Figure) * engine.nr_figures);

    // create deep copy of figures points
    int figure_nr;
    for (figure_nr = 0; figure_nr < engine.nr_figures; figure_nr++) {
        Figure *figure = engine.figures + figure_nr;
        Figure *trans_figure = engine.transformed_figures + figure_nr;
        trans_figure->points = (Vector3f *) malloc(sizeof(Vector3f) * trans_figure->nr_points);
        memcpy(trans_figure->points, figure->points, sizeof(Vector3f) * trans_figure->nr_points);

        Lines2D *lines = engine.figure_lines + figure_nr;

        lines->nr_points = figure->nr_points;
        lines->points = (Vector2f *) malloc(sizeof(Vector2f) * lines->nr_points);

        lines->nr_lines =
                figure->planes->nr_points * figure->nr_planes;    // assuming all planes have same nr of points
        lines->lines = (Line2D *) malloc(sizeof(Line2D) * lines->nr_lines);
    }
    engine.transformed_figures->points->x = 5;



    // Eye point_nr transformation matrix
    Vector3f *eye_point = (Vector3f *) malloc(sizeof(Vector3f));
    loadVector3f(eye_point, 5, 0, 0, 1);
    engine.eyeTransMatrix = eyePointTransM(eye_point);

    engine.rotation_angle = 0;

    // Main loop
    mainLoop(renderer);

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    int i;
    for (i = 0; i < engine.nr_figures; i++) {
        destroyFigure(engine.figures + i);
    }
}

void mainLoop(SDL_Renderer *renderer) {
    int running = 1;
    SDL_Event event;
    while (running) {
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // physics
        engine.rotation_angle += 0.01f;
        if (engine.rotation_angle > 2 * M_PI) engine.rotation_angle -= 2 * (float) M_PI;

        engine.transMatrix = rotateMZ(engine.rotation_angle);

        // Draw
        draw(renderer);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }
}

void draw(SDL_Renderer *renderer) {
    // copy figure points and apply transformations
    int figure_nr;
    for (figure_nr = 0; figure_nr < engine.nr_figures; figure_nr++) {
        Figure *figure = engine.figures + figure_nr;
        Figure *trans_figure = engine.transformed_figures + figure_nr;

        memcpy(trans_figure->points, figure->points, sizeof(Vector3f) * trans_figure->nr_points);

        applyTransformation(trans_figure, engine.transMatrix);
        applyTransformation(trans_figure, engine.eyeTransMatrix);
    }

    projectFigures();
    drawLines(renderer);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"

void draw2DLine(SDL_Renderer *renderer, Line2D *line2d, Vector2f *points) {
    Vector2f *p1 = projectCoordinateWorldToWindow(points + line2d->p1_index);
    Vector2f *p2 = projectCoordinateWorldToWindow(points + line2d->p2_index);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, (int) floorf(p1->x), (int) floorf(p1->y), (int) floorf(p2->x), (int) floorf(p2->y));

    free(p1);
    free(p2);
}

#pragma clang diagnostic pop

void drawLines(SDL_Renderer *renderer) {
    int i, line;
    for (i = 0; i < engine.nr_figures; i++) {
        Lines2D *figure_lines = engine.figure_lines + i;

        for (line = 0; line < figure_lines->nr_lines; line++) {
            draw2DLine(renderer, figure_lines->lines + line, figure_lines->points);
        }
    }
}

void draw2DLines(SDL_Renderer *renderer, Lines2D *lines2d) {
    int i;
    for (i = 0; i < lines2d->nr_lines; i++) {
        draw2DLine(renderer, lines2d->lines + i, lines2d->points);
    }
}

Vector2f *projectCoordinateWorldToWindow(Vector2f *point) {
    Vector2f *new_point = (Vector2f *) malloc(sizeof(Vector2f));

    // calculate alpha value
    float alpha_x = (point->x - x_min) / (x_max - x_min);
    float alpha_y = (point->y - y_min) / (y_max - y_min);

    // linear interpolation of the coordinate
    new_point->x = lerp(0, (float) window_width, alpha_x);
    new_point->y = lerp(0, (float) window_height, alpha_y);

    return new_point;
}

void projectFigures() {
    int i, j, k, point;

    float d = 1;

    // figures
    for (i = 0; i < engine.nr_figures; i++) {
        Figure *figure = engine.transformed_figures + i;
        Lines2D *lines = engine.figure_lines + i;

        // project all points
        for (point = 0; point < figure->nr_points; point++) {
            Vector3f *f_point = figure->points + point;
            lines->points[point].x = (d * f_point->x) / (-f_point->z);
            lines->points[point].y = (d * f_point->y) / (-f_point->z);
        }

        // planes
        for (j = 0; j < figure->nr_planes; j++) {
            Plane *plane = figure->planes + j;

            // create lines
            for (k = 0; k < plane->nr_points; k++) {
                lines->lines[j * plane->nr_points + k].p1_index = plane->point_indices[k];
                if (k != plane->nr_points - 1)
                    lines->lines[j * plane->nr_points + k].p2_index = plane->point_indices[k + 1];
                else
                    lines->lines[j * plane->nr_points + k].p2_index = plane->point_indices[0];
            }
        }
    }
}