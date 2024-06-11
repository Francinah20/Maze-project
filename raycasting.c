#include "raycasting.h"
#include "sdl_utils.h"
#include <math.h>

#define FOV_ANGLE 60
#define WALL_HEIGHT 400
#define WALL_COLOR_NS_R 255
#define WALL_COLOR_NS_G 0
#define WALL_COLOR_NS_B 0
#define WALL_COLOR_EW_R 0
#define WALL_COLOR_EW_G 255
#define WALL_COLOR_EW_B 0
#define GROUND_COLOR_R 0
#define GROUND_COLOR_G 0
#define GROUND_COLOR_B 255

void cast_rays(SDL_Renderer *renderer, int camera_x, int camera_y, int camera_angle, int map[][SCREEN_HEIGHT], int map_width, int map_height)
{
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double ray_angle = (camera_angle - (FOV_ANGLE / 2)) + ((double)x / SCREEN_WIDTH) * FOV_ANGLE;
        double distance_to_wall = 0;
        int hit_wall = 0;
        int wall_orientation = 0; // 0: NS (North/South), 1: EW (East/West)

        double ray_x = camera_x;
        double ray_y = camera_y;

        double angle_radians = ray_angle * M_PI / 180.0;
        double x_step = cos(angle_radians) / 10;
        double y_step = sin(angle_radians) / 10;

        while (!hit_wall && distance_to_wall < 1000) {
            distance_to_wall += 0.1;
            int test_x = (int)(ray_x + x_step * distance_to_wall);
            int test_y = (int)(ray_y + y_step * distance_to_wall);

            // Check if ray is out of bounds
            if (test_x < 0 || test_x >= map_width || test_y < 0 || test_y >= map_height) {
                hit_wall = 1;
                distance_to_wall = 1000;
            } else if (map[test_x][test_y] == 1) { // Check if ray hits a wall
                hit_wall = 1;

                // Calculate distance to the wall
                distance_to_wall *= cos((ray_angle - camera_angle) * M_PI / 180.0);

                // Determine wall orientation
                if (fabs(test_x - ray_x) > fabs(test_y - ray_y))
                    wall_orientation = 1; // EW
                else
                    wall_orientation = 0; // NS

                // Calculate wall height based on distance
                int wall_height = (int)(WALL_HEIGHT / distance_to_wall);

                // Draw the wall with appropriate color
                if (wall_orientation == 0) { // North/South
                    draw_vertical_line(renderer, x, (SCREEN_HEIGHT - wall_height) / 2, (SCREEN_HEIGHT + wall_height) / 2, WALL_COLOR_NS_R, WALL_COLOR_NS_G, WALL_COLOR_NS_B);
                } else { // East/West
                    draw_vertical_line(renderer, x, (SCREEN_HEIGHT - wall_height) / 2, (SCREEN_HEIGHT + wall_height) / 2, WALL_COLOR_EW_R, WALL_COLOR_EW_G, WALL_COLOR_EW_B);
                }
            }
        }

        // Draw ground and ceiling
        draw_vertical_line(renderer, x, 0, (SCREEN_HEIGHT - WALL_HEIGHT) / 2, GROUND_COLOR_R, GROUND_COLOR_G, GROUND_COLOR_B);
        draw_vertical_line(renderer, x, (SCREEN_HEIGHT + WALL_HEIGHT) / 2, SCREEN_HEIGHT, GROUND_COLOR_R, GROUND_COLOR_G, GROUND_COLOR_B);
    }
}

