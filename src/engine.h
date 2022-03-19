#ifndef C_TEST_ENGINE_H
#define C_TEST_ENGINE_H

#include <SDL2/SDL.h>
#include "DataStructures/Line2D.h"
#include "DataStructures/Figure.h"

static const int window_width = 1024;
static const int window_height = 1024;

static const float x_min = -5;
static const float x_max = 5;
static const float y_min = -5;
static const float y_max = 5;

static Figures figures;

void run();

void mainLoop(SDL_Renderer *renderer);

void draw(SDL_Renderer *renderer);

void draw2DLine(SDL_Renderer *renderer, Line2D *line2d, Vector2f *points);

void draw2DLines(SDL_Renderer *renderer, Lines2D *lines2d);

Vector2f *projectCoordinateWorldToWindow(Vector2f *point);

#endif //C_TEST_ENGINE_H
