/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:42:51 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 15:00:39 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t	r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ceiling_and_floor(t_general *G)
{
	unsigned short	x;
	unsigned short	y;
	short			h;
	short			w;

	x = 0;
	w = (short)G->img->width;
	h = (short)G->img->height;
	while (x < w)
	{
		y = 0;
		while (y < h / 2)
		{
			mlx_put_pixel(G->img, x, ++y,
				ft_pixel(G->map->ceil[0], G->map->ceil[1],
					G->map->ceil[2], 0x000000FF));
		}
		while (y < h - 1)
		{
			mlx_put_pixel(G->img, x, ++y,
				ft_pixel(G->map->floor[0], G->map->floor[1],
					G->map->floor[2], 0x000000FF));
		}
		x++;
	}
}

void	texture(t_texture *t, t_wall *w, t_general *G, t_array *r)
{
	t->height = (G->img->height) / w->wall_dist;
	t->start = (G->img->height / 2) - (t->height / 2);
	t->end = (G->img->height / 2) + (t->height / 2);
	if (t->start < 0)
		t->start = 0;
	if (t->end >= (int)(G->img->height))
		t->end = G->img->height - 1;
	if (w->hit_ax == 0)
		t->wall_x = G->vec[X].y + (w->wall_dist * r->dir[Y]);
	else
		t->wall_x = G->vec[X].x + (w->wall_dist * r->dir[X]);
}

void	set_texture(t_texture *t, t_wall *wall, mlx_texture_t *text, t_array *r)
{
	t->wall_x -= floor(t->wall_x);
	t->pix[X] = (int)(t->wall_x * (double)text->width);
	if ((wall->hit_ax == 0 && r->dir[X] > 0)
		|| (wall->hit_ax == 1 && r->dir[Y] < 0))
		t->pix[X] = text->width - t->pix[X] - 1;
}

void	walls(t_wall *w, short x, t_general *G, t_array *r)
{
	t_texture		t;
	mlx_texture_t	*wall;
	int32_t			pixel;
	int				i;

	i = w->wall_hit;
	wall = G->walls[i];
	texture(&t, w, G, r);
	set_texture(&t, w, wall, r);
	t.step = (double)(wall->height) / t.height;
	t.pos = (t.start - (G->img->height / 2) + (t.height / 2)) * t.step;
	while (t.start < t.end)
	{
		t.pix[Y] = t.pos;
		pixel = (t.pix[Y] * wall->width + t.pix[X]) * 4;
		mlx_put_pixel(G->img, x, t.start, ft_pixel(wall->pixels[pixel + 0],
				wall->pixels[pixel + 1], wall->pixels[pixel + 2], 0x000000FF));
		t.pos += t.step;
		t.start++;
	}
}
