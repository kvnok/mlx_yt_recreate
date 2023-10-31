#include "../include/stuff.h"

char **fill_map(t_data *data) {
	int x;
	int y;

	x = 0;
	y = 0;
	data->map = malloc(sizeof(char *) * (mapY + 1));
	// char random_change[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '1'};

	srand(time(NULL)); // set randomizing seed to current time

	while (y < mapY) {
		data->map[y] = malloc(sizeof(char) * (mapX + 1));
		x = 0;
		while (x < mapX) {
			if (x == 0 || x == mapX - 1 || y == 0 || y == mapY - 1) {
				data->map[y][x] = '1';
			}
			else {
				data->map[y][x] = '0';
			}
			// else {
			// 	data->map[y][x] = random_change[rand() % 10];
			// }
			x++;
		}
		data->map[y][x] = '\0';
		y++;
	}
	data->map[3][3] = '1';
	data->map[4][2] = '1';
	// data->map[4][3] = '1';
	data->map[4][4] = '1';
	data->map[5][3] = '1';
	data->map[y] = NULL;
	print_map(data->map);
	return data->map;
}

void init_data(t_data *data) {
	data->mlx = mlx_init(WIDTH, HEIGHT, "mlx42pilot", true); //not out of bounds proof
	// data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT); //not out of bounds proof
	data->map = fill_map(data);
	data->colors[0] = red;
	data->colors[1] = green;
	data->colors[2] = blue;
	data->colors[3] = black;
	data->colors[4] = white;
	data->colors[5] = grey;
	data->colors[6] = yellow;

	data->screen_map_w = mapX * mapS;
	data->screen_map_h = mapY * mapS;
	// data->mlx = mlx_init(data->screen_map_w, data->screen_map_h, "mlx42pilot", true);
	data->img = mlx_new_image(data->mlx, data->screen_map_w, data->screen_map_h);
	data->keep_going = true;

	data->player = malloc(sizeof(t_player));
	// old player init
	// for (int i = 2; i < mapX; i++) {
	// 	if (data->map[2][i] == '0') {
	// 		data->player->px = i * mapS;
	// 		break;
	// 	}
	// }
	data->player->width = mapS/4;
	data->player->height = mapS/4;

	data->player->px = 400;
	data->player->py = 400;

	data->player->pa = 0;
	data->player->pdx = cos(degrees_to_radians(data->player->pa));
	data->player->pdy = -sin(degrees_to_radians(data->player->pa));
	// bres
	data->bres = malloc(sizeof(t_bres));
	data->bres->x1 = 0;
	data->bres->y1 = 0;
	data->bres->x2 = 0;
	data->bres->y2 = 0;
}
