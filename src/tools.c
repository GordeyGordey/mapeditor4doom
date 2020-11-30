#include "../include/map.h"

void	find_remove(t_map *map, int x, int y)
{
	t_nod *tmp;

	tmp = map->nod;
	while(tmp)
	{
		if ((tmp->x1 + map->z_x) == x || (tmp->y1 + map->z_x) == y ||
		(tmp->x2 + map->z_x) == x || (tmp->y2 + map->z_x) == y)
			tmp->removeflag = 1;
		tmp = tmp->nxt;
	}
}

void	edit_tool(t_map *map, int index)
{
	int i;

	i = -1;
	edit_blocktexture(map, -1);
	while (++i < 9)
	{
		if (i == index)
			map->inter_tex[i]->active = 1;
		else
			map->inter_tex[i]->active = 0;
	}
}

void	edit_blocktexture(t_map *map, int index)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (i == index)
			map->block_tex[i]->active = 1;
		else
			map->block_tex[i]->active = 0;
	}
}



void	wall_editor(t_map *map, int x, int y)
{
	int x1;
	int y1;

	if (map->click == 0 && interface_click(map, x, y))
	{
		map->click = 1;
		map->x_c = x;
		map->y_c = y;
		find_coord(map, &(map->x_c), &(map->y_c));
	}
	else if (interface_click(map, x, y))
	{
		map->click = 0;
		x1 = (x - map->z_x);
		y1 = (y - map->z_y);
		find_coord(map, &x, &y);
		add_node(map, x, y);
		map->nod->index = nod_len(map->nod);
	}
}