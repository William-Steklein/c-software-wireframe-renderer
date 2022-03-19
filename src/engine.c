#include "engine.h"
#include "utils/utils.h"

void run() {
    // Load figures
    figures.nr_figures = 0;
//    figures.figures = (Figure *) malloc(sizeof(Figure) * figures.nr_figures);

//    figures.figures = createCube();

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Simple C Graphics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          window_width,
                                          window_height, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Main loop
    mainLoop(renderer);

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

//    int i;
//    for (i = 0; i < figures.nr_figures; i++) {
//        destroyFigure(figures.figures + i);
//    }
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

        // Draw
        draw(renderer);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }
}

void draw(SDL_Renderer *renderer) {

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