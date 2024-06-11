#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>

/* Cast rays and draw walls using raycasting */
void cast_rays(SDL_Renderer *renderer, int camera_x, int camera_y, int camera_angle, int map[][SCREEN_HEIGHT], int map_width, int map_height);

#endif /* RAYCASTING_H */

