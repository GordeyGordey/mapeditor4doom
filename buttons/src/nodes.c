#include "../include/map.h"
#include <math.h>

t_nod	*n_cr(short x1, short y1, short x2, short y2)
{
	t_nod *a;

	// printf("x1 %d y1 %d x2 %d y2 %d\n", x1, y1, x2, y2);
	a = (t_nod*)malloc(sizeof(t_nod));
	a->x1 = x1;
	a->y1 = y1;
	a->x2 = x2;
	a->y2 = y2;
	a->nxt = NULL;
	return (a);
}

void add_node(t_map *mp, int x, int y)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(mp->x_clck - mp->z_x, mp->y_clck  - mp->z_y, x - mp->z_x, y - mp->z_y);
	if (mp->nod == NULL)
	{
		mp->nod = n;
		return;
	}
	else
	{
		cur = mp->nod;
		while (cur->nxt)
		{
			cur = cur->nxt;
		}
		cur->nxt = n;
	}
}

void draw_gr(t_map *map, int x, int y, t_color color)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		draw_color(map, pixel, GREEN);
	}
}

void draw_pr(t_map *map, int x, int y, unsigned char c)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		map->inter_tex[0]->s[pixel] = c;
		map->inter_tex[0]->s[++pixel] = 0;
		map->inter_tex[0]->s[++pixel] = c;
	}
}

void draw_node(t_map *map, t_nod *n)
{
	int x1;
	int y1;
	int x2;
	int y2;

	int dx;
	int dy;
	int er;
	int de;

	int i;
	int j;

	int diry;
	int di;

	x1 = n->x1 + map->z_x;
	x2 = n->x2 + map->z_x;
	if (x1 < 0 && x2 < 0)
		return;
	y1 = n->y1 + map->z_y;
	y2 = n->y2 + map->z_y;
	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	er = 0;
	de = dy + 1;
	j = y1;
	i = x1;
	di = 0;
	
	if (dx > dy)
	{
		i = x1;
		j = y1;
		di = (x2 - x1) / dx;
		diry = y2 - y1;
		de = dy + 1;
		if (diry > 0)
			diry = 1;
		if (diry < 0)
			diry = -1;
		
		while (i != x2)
		{
			draw_gr(map, i, j, GREEN);
			er += de;
			if (er >= dx + 1)
			{
				j += diry;
				er = er - (dx + 1);
			}
			i += di;
		}
	}
	else if (dy != 0)
	{
		i = y1;
		j = x1;
		di = (y2 - y1) / dy;
		diry = x2 - x1;
		de = dx + 1;
		if (diry > 0)
			diry = 1;
		if (diry < 0)
			diry = -1;
		
		while (i != y2)
		{
			draw_gr(map, j, i, GREEN);
			er += de;
			if (er >= dy + 1)
			{
				j += diry;
				er = er - (dy + 1);
			}
			i += di;
		}
	}
	bigdot(map, x1, y1, RED);
	bigdot(map, x2, y2, RED);
}

void draw_nodes(t_map *map)
{
	t_nod *n;

	n = map->nod;
	if (n == NULL)
		return;
	while (n)
	{
		draw_node(map, n);
		n = n->nxt;
	}
}

int sq(int x1, int y1, int x2, int y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	find_coord(t_map *map, int *x, int *y)
{
	int x1;
	int y1;
	int abs1;
	int abs2;
	t_nod *nod;

	nod = map->nod;
	x1 = *x;
	y1 = *y;
	abs1 = 50;
	if (!nod)
		return ;
	while (nod)
	{
		if (abs(nod->x1 - *x) < 5 && abs(nod->y1 - *y) < 5)
		{
			abs2 = sq(*x, *y, nod->x1, nod->y1);
			if (abs2 < abs1)
			{
				abs1 = abs2;
				x1 = nod->x1;
				y1 = nod->y1;
			}
		}
		if (abs(nod->x2 - *x) < 5 && abs(nod->y2 - *y) < 5)
		{
			abs2 = sq(*x, *y, nod->x2, nod->y2);
			if (abs2 < abs1)
			{
				abs1 = abs2;
				x1 = nod->x2;
				y1 = nod->y2;
			}
		}
		nod = nod->nxt;
	}
	if (abs1 < 5)
	{
		*x = x1;
		*y = y1;
	}
}