#include "Renderer.h"

Renderer *renderer_create(int viewport_width, int viewport_height) {
    Renderer *renderer = (Renderer *) malloc(sizeof(Renderer));
    renderer->viewport_width = viewport_width;
    renderer->viewport_height = viewport_height;

    // SDL
    SDL_Init(SDL_INIT_VIDEO);
    renderer->sdl_window = SDL_CreateWindow("Simple C Graphics Engine", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            renderer->viewport_width,
                                            renderer->viewport_height, SDL_WINDOW_OPENGL);

    renderer->sdl_renderer = SDL_CreateRenderer(renderer->sdl_window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return renderer;
}

void renderer_destroy(Renderer *renderer) {
    SDL_DestroyRenderer(renderer->sdl_renderer);
    SDL_DestroyWindow(renderer->sdl_window);
    SDL_Quit();
}

void renderer_clear(Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer->sdl_renderer);
}

void renderer_draw_line(Renderer *renderer, int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(renderer->sdl_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer->sdl_renderer, x1, y1, x2, y2);
}

void renderer_show(Renderer *renderer) {
    SDL_RenderPresent(renderer->sdl_renderer);
}
