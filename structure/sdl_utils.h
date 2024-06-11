#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>

/* Initialize SDL and create a window */
SDL_Window *init_window(int width, int height, const char *title);

/* Destroy window and quit SDL */
void close_window(SDL_Window *window);

/* Draw a pixel on the screen */
void draw_pixel(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b);

/* Draw a vertical line on the screen */
void draw_vertical_line(SDL_Renderer *renderer, int x, int y1, int y2, Uint8 r, Uint8 g, Uint8 b);

#endif /* SDL_UTILS_H */

