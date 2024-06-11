
#include <SDL2/SDL.h>
#include "sdl_utils.h"
#include "maze.h"
#include "raycasting.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    SDL_Window *window = init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Raycasting");
    if (!window) {
        fprintf(stderr, "Failed to initialize SDL window\n");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer\n");
        close_window(window);
        return 1;
    }
include "raycasting.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    SDL_Window *window = init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Raycasting");
    if (!window) {
        fprintf(stderr, "Failed to initialize SDL window\n");
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer\n");
        close_window(window);
        return 1;
    }

    int map[SCREEN_WIDTH][SCREEN_HEIGHT];
    // Initialize map with example data
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            map[j][i] = (i == 0 || i == SCREEN_HEIGHT - 1 || j == 0 || j == SCREEN_WIDTH - 1) ? 1 : 0;
        }
    }

    int camera_x = SCREEN_WIDTH / 2;
    int camera_y = SCREEN_HEIGHT / 2;
    int camera_angle = 0;

    // Game loop
    SDL_Event event;
    int running = 1;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT)
                    camera_angle -= 5;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    camera_angle += 5;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw walls using raycasting
        cast_rays(renderer, camera_x, camera_y, camera_angle, map, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    close_window(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

