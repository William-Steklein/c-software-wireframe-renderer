#ifndef C_TEST_ENGINE_H
#define C_TEST_ENGINE_H

#include <SDL2/SDL.h>
#include "utils/utils.h"
#include "DataStructures/Line2D.h"
#include "DataStructures/Figure.h"

static const int window_width = 1024;
static const int window_height = 1024;

static const float x_min = -1;
static const float x_max = 1;
static const float y_min = -1;
static const float y_max = 1;

static int exported = 0;

// todo: expand & refactor engine struct
typedef struct Engine Engine;
struct Engine {
    float rotation_angle;
    float figure_scale;
    Matrix *transMatrix;
    Matrix *eyeTransMatrix;

    int nr_figures;
    Figure *figures;
    Figure *transformed_figures;

    Lines2D *figure_lines;
};

static Engine engine;

void run();

void mainLoop(SDL_Renderer *renderer);

void draw(SDL_Renderer *renderer);

void draw2DLine(SDL_Renderer *renderer, Line2D *line2d, Vector2f *points);

void drawLines(SDL_Renderer *renderer);

void draw2DLines(SDL_Renderer *renderer, Lines2D *lines2d);

Vector2f *projectCoordinateWorldToWindow(Vector2f *point);

void projectFigures();

#endif //C_TEST_ENGINE_H
