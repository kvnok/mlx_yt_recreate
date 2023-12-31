#include "../include/stuff.h"

void remake_image(t_data *data) {
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// data->img = mlx_new_image(data->mlx, data->screen_map_w, data->screen_map_h);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void bres_draw_line(t_data *data)
{
	// print_coords(data);
	int dx = abs(data->bres->x2 - data->bres->x1); //distance x coords
	int dy = abs(data->bres->y2 - data->bres->y1); //distance y coords
	int sx = data->bres->x1 < data->bres->x2 ? 1 : -1; //slope x
	int sy = data->bres->y1 < data->bres->y2 ? 1 : -1; //slope y
	int err = dx - dy; //move vertical or horizontal
	int e2; //error correction * 2
	while (data->bres->x1 != data->bres->x2 && data->bres->y1 != data->bres->y2) {
		mlx_put_pixel(data->img, data->bres->x1, data->bres->y1, data->bres->color);
		e2 = err * 2; //err * 2 at the start of next calculation
		if (e2 > -dy) {
			err -= dy;
			data->bres->x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			data->bres->y1 += sy;
		}
	}
}

void topdown_drawline(t_data *data) {
	int px = data->player->px;
	int py = data->player->py;
	float pdx = data->player->pdx;
	float pdy = data->player->pdy;
	data->bres->x1 = px;
	data->bres->y1 = py;
	data->bres->x2 = px+(pdx*32);
	data->bres->y2 = py+(pdy*32);
	data->bres->color = 0x0000FFFF;
	bres_draw_line(data);
}

void rotation(t_data *data, int modifier) {
	data->player->pa += (rotationspeed * modifier);
	data->player->pa = fix_angle(data->player->pa);
	data->player->pdx = cos(degrees_to_radians(data->player->pa));
	data->player->pdy = -sin(degrees_to_radians(data->player->pa));
}

void back_and_forth(t_data *data, int modifier) {
	float newX = data->player->px + data->player->pdx*(movespeed * modifier);
	float newY = data->player->py + data->player->pdy*(movespeed * modifier);
	float testmapX = newX / mapS;
	float testmapY = newY / mapS;
	if (data->map[(int)testmapY][(int)testmapX] == '0') {
		data->player->px = newX;
		data->player->py = newY;
	}
}

void strafe(t_data *data, int modifier) {
	float newX = data->player->px + data->player->pdy*(movespeed * modifier);
	float newY = data->player->py - data->player->pdx*(movespeed * modifier);
	float testmapX = newX / mapS;
	float testmapY = newY / mapS;
	if (data->map[(int)testmapY][(int)testmapX] == '0') {
		data->player->px = newX;
		data->player->py = newY;
	}
}

void loop_hook(void *param) {
	t_data *data;

	data = (t_data *)param;
	remake_image(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE)) {
		data->keep_going = false;
		cleanup(data);
		exit(0);
	}
	//rotate
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) {
		rotation(data, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) {
		rotation(data, -1);
	}
	//forward and backward
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) {
		back_and_forth(data, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) {
		back_and_forth(data, -1);
	}
	//strafe
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) {
		strafe(data, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) {
		strafe(data, -1);
	}
	if (data->keep_going == true) {
		fill_coords(data, 0, 0, data->screen_map_w, data->screen_map_h, white);
		topdown_blocks(data);
		draw_2D_verticals(data);
		draw_2D_horizontals(data);
		draw_player_square(data, data->player->px, data->player->py, red);
		topdown_drawline(data);
		// fill_coords(data, data->screen_map_w, 0,data->screen_map_w*2, 320, white);
		fill_coords(data, data->screen_map_w, 0,data->screen_map_w*2, 160, yellow);
		fill_coords(data, data->screen_map_w, 160,data->screen_map_w*2, 320, green);
		drawRays2D(data);
	}
}
