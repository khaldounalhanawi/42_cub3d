#include "data_types.h"

#include <stdlib.h>
#include <string.h>

static void	set_player(t_player *player, char spawn, int x, int y)
{
	player->pos_x = x + 0.5;
	player->pos_y = y + 0.5;
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
	player->plane_x = 0.0;
	player->plane_y = 0.66;

	if (spawn == 'N')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	else if (spawn == 'S')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	else if (spawn == 'E')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (spawn == 'W')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}

t_game	example_game(void)
{
	t_game	game;
	t_map	mymap;

	mymap.grid = NULL;
	mymap.height = 5;
	mymap.width = 5;
	game.map = &mymap;


	const char *map_lines[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL
	};

	int i;
	int max_width = 0;

	// Count rows and compute max width
	for (i = 0; map_lines[i]; i++)
	{
		int len = strlen(map_lines[i]);
		if (len > max_width)
			max_width = len;
	}
	game.map->height = i;
	game.map->width = max_width;

	// Allocate and copy rows
	game.map->grid = malloc(sizeof(char *) * game.map->height);
	for (i = 0; i < game.map->height; i++)
	{
		game.map->grid[i] = strdup(map_lines[i]);
		// Detect player spawn
		char *p = strpbrk(map_lines[i], "NSEW");
		if (p)
			set_player(&game.player, *p, p - map_lines[i], i);
	}

	// Screen size
	game.screen_width = 800;
	game.screen_height = 600;

	// Floor & ceiling
	game.floor_color = (220 << 16) | (100 << 8) | 0; // F 220,100,0
	game.ceiling_color = (225 << 16) | (30 << 8) | 0; // C 225,30,0

	// Textures placeholder
	for (i = 0; i < 4; i++)
		game.textures[i].img = NULL;

	game.mlx = NULL;
	game.win = NULL;
	game.ray_hits = NULL;

	return game;
}
