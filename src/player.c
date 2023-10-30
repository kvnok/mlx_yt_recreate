#include "../include/stuff.h"

void draw_player_square(t_data *data, int x, int y, int color) {
	int halfwidth = data->player->width/2;
	int halfheight = data->player->height/2;
	fill_coords(data, x-halfwidth, y-halfheight, x+halfwidth, y+halfheight, color);
}
