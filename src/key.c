#include "../include/map.h"

int		mkey(int key, int x, int y, t_map *map)
{
	if (key == 1)
	{
		if (map->inter_tex[6]->active)
			wall_editor(map, x, y);
		if (map->inter_tex[8]->active)
			remove_tool(map, x, y);
		if (map->inter_tex[4])
			change_texture(map, x, y);
	}
	SDL_UpdateWindowSurface(map->win);
	return (0);
}

int		pkey(int key, t_map *map)
{
	if (key == 27)
		exit(1);
	if (map->inter_tex[16]->active == 1)
	{
		if (key == 80)
		{
			map->change_plus -= 5;
			draw_changer_texture(map);
		}
		if (key == 79)
		{
			map->change_plus += 5;
			draw_changer_texture(map);
		}
	}
	// printf("%d\n", key);
	return (0);
}