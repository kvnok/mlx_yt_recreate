#include "../include/stuff.h"

void fill_coords(t_data *data, int x1, int y1, int x2, int y2, int color) {
	int x;
	int y;

	x = x1;
	y = y1;
	while (x < x2) { //left to right
		y = y1;
		while (y < y2) { // top to bottom
			mlx_put_pixel(data->img, x, y, color);
			y++;
		}
		x++;
	}
}

void draw_2D_verticals(t_data *data) {
	int x = 0;
	while (x < data->screen_map_w) {
		fill_coords(data, x, 0, x + 1, data->screen_map_h, grey);
		x += mapS;
	}
}

void draw_2D_horizontals(t_data *data) {
	int y = 0;
	while (y < data->screen_map_h) {
		fill_coords(data, 0, y, data->screen_map_w, y + 1, grey);
		y += mapS;
	}
}

void topdown_blocks(t_data *data) {
	int x = 0;
	int y = 0;
	while (y < mapY) {
		x = 0;
		while (x < mapX) {
			if (data->map[y][x] == '1') {
				fill_coords(data, x * mapS, y * mapS, (x + 1) * mapS, (y + 1) * mapS, black);
			}
			x++;
		}
		y++;
	}
	// printf("topdown_blocks done\n");
}
