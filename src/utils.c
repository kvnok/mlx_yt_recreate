#include "../include/stuff.h"

int32_t pixel_select(int32_t r, int32_t g, int32_t b, int32_t a) {
	return (r << 24 | g << 16 | b << 8 | a);
}

float degrees_to_radians(float angle) {
	return (angle * (M_PI / 180));
}

int fix_angle(int angle) {
	// printf("angle: %d\n", angle);
	if (angle > 359) {
		angle -= 360;
	}
	if (angle < 0) {
		angle += 360;
	}
	return angle;
}

void print_map(char **map) {
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < mapY) {
		x = 0;
		while (x < mapX) {
			printf("|%c|", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

