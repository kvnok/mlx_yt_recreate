#include "../include/stuff.h"

void free_map(t_data *data) {
	int y;
	y = 0;
	// print_map(data->map);
	while (y < mapY) {
		// char **row = &(data->map[y]);
		free(data->map[y]);
		y++;
	}
	free(data->map);
}

void cleanup(t_data *data) {
	free_map(data);
	free(data->player);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
}
