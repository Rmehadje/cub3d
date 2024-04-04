/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:19:54 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/04 15:39:21 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cast_ray2(t_array *r, char **map)
{
	int hx;

	hx = 0;
	while (true)
	{
		if (r->step_dis[X] < r->step_dis[Y])
		{
			r->step_dis[X] += r->dir_dis[X];
			r->pos[X] += r->s[X];
			r->haxis = X;
		}
		else
		{
			r->step_dis[Y] += r->dir_dis[Y];
			r->pos[Y] += r->s[Y];
			r->haxis = Y;
		}
		if (map[r->pos[1]][r->pos[0]] == '1')
			break ;
	}
	hx = r->haxis;
	return (hx);
}
void	d_collision(t_array *r, t_wall *wall)
{
	if (wall->hit_ax == 0)
	{
		wall->wall_dist = r->step_dis[X] - r->dir_dis[X];
		wall->wall_hit = r->h_side[X];
	}
	else
	{
		wall->wall_dist = r->step_dis[Y] - r->dir_dis[Y];
		wall->wall_hit = r->h_side[Y];
	}
}

void	cast_ray(t_general *G, char **map)
{
	uint32_t x;
	t_array	r;
	t_wall	wall;

	x = 0;
	while (x < G->img->width)
	{
		r.dir[X] = G->vec[1].x + (G->vec[2].x * r.camx);
		r.dir[Y] = G->vec[1].y + (G->vec[2].y * r.camx);
		r.pos[X] = G->vec[0].x;
		r.pos[Y] = G->vec[0].y;
		r.camx = (2 * x / (double)G->img->width - 1);
		if (r.dir[X] < 0)
			dirxL(&r, G->vec); 
		else
			dirxR(&r, G->vec);
		if (r.dir[Y] < 0)
			diryu(&r, G->vec);
		else
			diryd(&r, G->vec);
		wall.hit_ax = cast_ray2(&r, map);
		d_collision(&r, &wall);
		walls(&wall, x, G, &r);
		x++;
	}
}
