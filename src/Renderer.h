#ifndef SIMPLE_C_GRAPHICS_ENGINE_RENDERER_H
#define SIMPLE_C_GRAPHICS_ENGINE_RENDERER_H

#include <SDL2/SDL.h>

typedef struct Renderer Renderer;
struct Renderer {
    int viewport_width;
    int viewport_height;

    SDL_Renderer *sdl_renderer;
    SDL_Window *sdl_window;
};

Renderer *renderer_create(int viewport_width, int viewport_height);

void renderer_destroy(Renderer *renderer);

void renderer_clear(Renderer *renderer);

void renderer_draw_line(Renderer *renderer, int x1, int y1, int x2, int y2);

void renderer_show(Renderer *renderer);

#endif //SIMPLE_C_GRAPHICS_ENGINE_RENDERER_H
