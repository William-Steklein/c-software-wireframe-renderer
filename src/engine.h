#ifndef C_TEST_ENGINE_H
#define C_TEST_ENGINE_H

#include <SDL2/SDL.h>
#include "utils/utils.h"
#include "DataStructures/Line2D.h"
#include "DataStructures/Figure.h"
#include "DataStructures/Matrix.h"
#include "Renderer.h"

typedef struct Engine Engine;
struct Engine {
    Renderer *renderer;

    float world_view_x_min;
    float world_view_x_max;
    float world_view_y_min;
    float world_view_y_max;

    Matrix *eyeTransMatrix;

    int nr_figures;
    Figure *figures;

    Figure *transformed_figures;

    Lines2D *figure_lines;
};

static Engine engine;

void engine_run();

void engine_setup();

void engine_destroy();

void engine_main_loop();

void engine_draw();

void engine_draw_lines2d();

void engine_project_figures();

void engine_project_vector2df_ref_viewport(Vector2Df *point);

#endif //C_TEST_ENGINE_H
