#include "data_types.h"
#include "libft.h"

#include <stdlib.h>
#include <string.h>

t_init_data	example_data(void)
{
	t_init_data	data;
	t_map	*mymap;

	mymap = malloc (sizeof (t_map));
	data.map = mymap;

	const char *map_lines[] = {
		"1111111111111111111111111",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"100000000000000000000001",
		"1000000000000000000000111111",
		"1000000000000000000000000001",
		"1000000000000000000000000001",
		"1000000000000000000000000001",
		"10000000000000000000000000001",
		"10000000000000000001010000001",
		"10000000100000001000000000N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL};
	int i;
	int max_width = 0;

	// Count rows and compute max width
	for (i = 0; map_lines[i]; i++)
	{
		int len = strlen(map_lines[i]);
		if (len > max_width)
			max_width = len;
	}
	data.map->height = i;
	data.map->width = max_width;

	// Allocate and copy rows
	data.map->grid = malloc(sizeof(char *) * data.map->height);
	for (i = 0; i < data.map->height; i++)
	{
		data.map->grid[i] = strdup(map_lines[i]);
	}

	data.north_tex = ft_strdup ("./textures/North.xpm");
	data.south_tex = ft_strdup ("./textures/South.xpm");
	data.east_tex = ft_strdup ("./textures/East.xpm");
	data.west_tex = ft_strdup ("./textures/West.xpm");

	data.ceiling_color[0] = 135;
	data.ceiling_color[1] = 206;
	data.ceiling_color[2] = 235;

	data.floor_color[0] = 128;
	data.floor_color[1] = 128;
	data.floor_color[2] = 128;

	data.player_x = 5;
	data.player_y = 5;
	data.player_dir = 'N';

	return data;
}

/*	const char *map_lines[] = {
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
	};*/

/*
		const char *map_lines[] = {
		"1111111111111111111111111",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"10000000000000000000001",
		"1000000000000000000000111111",
		"1000000000000000000000000001",
		"1000000000000000000000000001",
		"1000000000000000000000000001",
		"10000000000000000000000000001",
		"10000000000000000001010000001",
		"10000000100000001000000000N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL
	};*/