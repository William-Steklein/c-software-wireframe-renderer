#include "engine.h"

void engine_run() {
    engine_setup();

    engine_main_loop();

    engine_destroy();
}

void engine_setup() {
    // renderer
    engine.renderer = renderer_create(1024, 1024);

    // world
    engine.world_view_x_min = -1;
    engine.world_view_x_max = 1;
    engine.world_view_y_min = -1;
    engine.world_view_y_max = 1;

    // load figures
    engine.nr_figures = 1;
    engine.figures = (Figure *) malloc(sizeof(Figure) * engine.nr_figures);
    engine.transformed_figures = (Figure *) malloc(sizeof(Figure) * engine.nr_figures);

    engine.figures = figure_import("torus.obj");
//    engine.figures = figure_create_cube();

    engine.figure_lines = (Lines2D *) malloc(sizeof(Lines2D) * engine.nr_figures);
    memcpy(engine.transformed_figures, engine.figures, sizeof(Figure) * engine.nr_figures);

    for (int figure_nr = 0; figure_nr < engine.nr_figures; figure_nr++) {
        Figure *figure = engine.figures + figure_nr;
        Figure *trans_figure = engine.transformed_figures + figure_nr;

        // create a deep copy of the figures
        trans_figure->points = (Vector3Df *) malloc(sizeof(Vector3Df) * trans_figure->nr_points);
        memcpy(trans_figure->points, figure->points, sizeof(Vector3Df) * trans_figure->nr_points);
//        figure_deep_copy(figure, trans_figure);

        // create empty instance of lines for this figure
        Lines2D *lines = engine.figure_lines + figure_nr;

        lines->nr_points = figure->nr_points;
        lines->points = (Vector2Df *) malloc(sizeof(Vector2Df) * lines->nr_points);

        lines->nr_lines =
                figure->planes->nr_points * figure->nr_planes;    // assuming all planes have same nr of points todo
        lines->lines = (Line2D *) malloc(sizeof(Line2D) * lines->nr_lines);
    }

    // eye point_nr transformation matrix
    Vector3Df *eye_point = (Vector3Df *) malloc(sizeof(Vector3Df));
    vector3df_load(eye_point, 5.f, 0, 0, 1);
    engine.eyeTransMatrix = matrix_create_eye_point_trans(eye_point);
}

void engine_destroy() {
    renderer_destroy(engine.renderer);
    free(engine.renderer);

    matrix_destroy(engine.eyeTransMatrix);
    free(engine.eyeTransMatrix);

    for (int i = 0; i < engine.nr_figures; i++) {
        figure_destroy(engine.figures + i);

        free(engine.transformed_figures[i].points);
//        figure_destroy(engine.transformed_figures + i);
    }
    free(engine.figures);
    free(engine.transformed_figures);
}

void engine_main_loop() {
    int running = 1;
    SDL_Event event;
    while (running) {
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // clear
        renderer_clear(engine.renderer);

        // draw
        engine_draw();

        // show
        renderer_show(engine.renderer);
    }
}

void engine_draw() {
    // copy figure points and apply transformations
    int figure_nr;
    for (figure_nr = 0; figure_nr < engine.nr_figures; figure_nr++) {
        Figure *figure = engine.figures + figure_nr;
        Figure *trans_figure = engine.transformed_figures + figure_nr;

        memcpy(trans_figure->points, figure->points, sizeof(Vector3Df) * trans_figure->nr_points);

        figure_apply_transformation(trans_figure, engine.eyeTransMatrix);
    }

    engine_project_figures();
    engine_draw_lines2d();
}

void engine_draw_lines2d() {
    int i, line;
    for (i = 0; i < engine.nr_figures; i++) {
        Lines2D *figure_lines = engine.figure_lines + i;

        for (line = 0; line < figure_lines->nr_lines; line++) {
            Vector2Df *p1 = figure_lines->points + (figure_lines->lines + line)->p1_index;
            Vector2Df *p2 = figure_lines->points + (figure_lines->lines + line)->p2_index;

            renderer_draw_line(engine.renderer, (int) floorf(p1->x), (int) floorf(p1->y), (int) floorf(p2->x),
                               (int) floorf(p2->y));
        }
    }
}

void engine_project_figures() {
    int i, j, k, point;

    float d = 1;

    // figures
    for (i = 0; i < engine.nr_figures; i++) {
        Figure *figure = engine.transformed_figures + i;
        Lines2D *lines = engine.figure_lines + i;

        // project all points
        for (point = 0; point < figure->nr_points; point++) {
            // projects to world view
            Vector3Df *f_point = figure->points + point;
            lines->points[point].x = (d * f_point->x) / (-f_point->z);
            lines->points[point].y = (d * f_point->y) / (-f_point->z);

            // projects to view frame
            engine_project_vector2df_ref_viewport(lines->points + point);
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

void engine_project_vector2df_ref_viewport(Vector2Df *point) {
    // calculate alpha value
    float alpha_x = (point->x - engine.world_view_x_min) / (engine.world_view_x_max - engine.world_view_x_min);
    float alpha_y = (point->y - engine.world_view_y_min) / (engine.world_view_y_max - engine.world_view_y_min);

    // linear interpolation of the coordinate
    float new_x = lerp(0, (float) engine.renderer->viewport_width, alpha_x);
    float new_y = lerp((float) engine.renderer->viewport_height, 0, alpha_y);

    point->x = new_x;
    point->y = new_y;
}
