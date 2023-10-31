#ifndef STUFF_H
# define STUFF_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
#include <time.h>

#define WIDTH 1024
#define HEIGHT 510

/*
could also test with
#define mapX 40
#define mapY 30
*/

#define mapX 8
#define mapY 8

#define mapS 64

#define red 0xFF0000FF
#define green 0x00FF00FF
#define blue 0x0000FFFF
#define black 0x000000FF
#define white 0xFFFFFFFF
#define grey 0x302F2CFF
#define yellow 0xFFFF00FF

#define rotationspeed 3
#define movespeed 5

typedef struct s_bres
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	uint32_t		color;
}	t_bres;

typedef struct s_player {
	// general
	int				width;
	int				height;
	// sorta new
	float 			px;
	float 			py;
	float			pdx;
	float			pdy;
	float			pa;
}	t_player;

typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint32_t		color;
	char			**map;
	uint32_t		colors[7];
	int				screen_map_w;
	int				screen_map_h;
	bool			keep_going;
	t_player		*player;
	t_bres			*bres;
}	t_data;

// init_fill_struct.c
char		**fill_map(t_data *data);
void		init_data(t_data *data);

// topdown.c
void		fill_coords(t_data *data, int x1, int y1, int x2, int y2, int color);
void		draw_2D_verticals(t_data *data);
void		draw_2D_horizontals(t_data *data);
void		topdown_blocks(t_data *data);

// utils.c
int32_t		pixel_select(int32_t r, int32_t g, int32_t b, int32_t a);
float		degrees_to_radians(float angle);
int			fix_angle(int angle);
void		print_map(char **map);

// loophook.c
void remake_image(t_data *data);
void bres_draw_line(t_data *data);
void topdown_drawline(t_data *data);
void rotation(t_data *data, int modifier);
void back_and_forth(t_data *data, int modifier);
void strafe(t_data *data, int modifier);
void loop_hook(void *param);

// player.c
void		draw_player_square(t_data *data, int x, int y, int color);

// cleanup.c
void		free_map(t_data *data);
void		cleanup(t_data *data);

// drawRays2D.c
void		drawRays2D(t_data *data);

#endif
