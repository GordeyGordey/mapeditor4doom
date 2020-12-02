#include "../include/map.h"

void init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
}

int		init_all(t_map *map)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	if (!(map->win = SDL_CreateWindow("Mapeditor", 200, 200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		return (0);
	init_interface(map);
	map->z_x = WIDTH / 2;
	map->z_y = HEIGHT / 2;
	map->click = 0;
	map->nod = NULL;
	map->wclick = 25;
	map->tmpclick = 0;
	map->showactive = 0;

	map->change_x = 0;
	map->change_y = 0;
	map->change_plus = 0;
	map->index_tex = -1;
	return (1);
}

void	init_interface(t_map *map)
{
	malloc_interface(map);
	malloc_block_texture(map);
	malloc_wall_texture(map);
	malloc_floorsky_texture(map);
	malloc_liquid_texture(map);
}