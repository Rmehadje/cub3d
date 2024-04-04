/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:42:51 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/04 15:39:30 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t	r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ceiling_and_floor(t_general *G)
{
	unsigned int x;
	unsigned int y;

	x = 0;
	while (x < G->img->width)
	{
		y = 0;
		while (y < G->img->height / 2)
		{
			mlx_put_pixel(G->img, x, y,
				ft_pixel(G->ceilingcolor[0], G->ceilingcolor[1], G->ceilingcolor[2], 255));
			y++;
		}
		while (y < G->img->height - 1)
		{
			mlx_put_pixel(G->img, x, y,
				ft_pixel(G->ceilingcolor[0], G->ceilingcolor[1], G->ceilingcolor[2], 255));
			y++;
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
		t->wall_x = G->vec[0].y + (w->wall_dist * r->dir[Y]);
		else
		t->wall_x = G->vec[0].x + (w->wall_dist * r->dir[X]);
}

void	set_texture(t_texture *t, t_wall *wall, mlx_texture_t *text, t_array *r)
{
	t->wall_x -= floor(t->wall_x);
	t->pix[0] = (int)(t->wall_x * (double)text->width);
	if ((wall->hit_ax == 0 && r->dir[Y] > 0)
		|(wall->hit_ax == 1 && r->dir[X] < 0))
		t->pix[0] = text->width - t->pix[0] - 1;
}

void	walls(t_wall *w, short x, t_general *G, t_array *r)
{
	t_texture t;
	mlx_texture_t	*wall;
	int			pixel;
	int			i;

	i = w->wall_hit;
	wall = G->walls[i];
	texture(&t, w, G, r);
	set_texture(&t, w, wall, r);
	t.step = (double)(wall->height) / t.height;
	t.pos = (t.start) - (G->img->height / 2) + (t.height / 2) * t.step;
	while (t.start < t.end)
	{
		t.pix[1] = t.pos;
		pixel = (t.pix[1] * wall->width + t.pix[0]) * 4;
		mlx_put_pixel(G->img, x, t.start, ft_pixel(wall->pixels[pixel + 0],
				wall->pixels[pixel + 1], wall->pixels[pixel + 2], 0));
		t.pos += t.step;
		t.start++;
	}
}
