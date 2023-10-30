#include "../include/stuff.h"

int main(int argc, char **argv) {
	t_data data;

	init_data(&data);
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop(data.mlx);
	cleanup(&data);
	return 0;
}
