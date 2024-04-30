/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:19:54 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 15:06:57 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cast_ray2(t_array *r, char **map)
{
	int	hx;

	hx = 0;
	while (true)
	{
		if (r->step_dis[X] < r->step_dis[Y])
		{
			r->step_dis[X] += r->dir_dis[X];
			r->pos[X] += r->s[X];
			hx = 0;
		}
		else
		{
			r->step_dis[Y] += r->dir_dis[Y];
			r->pos[Y] += r->s[Y];
			hx = 1;
		}
		if (map[r->pos[Y]][r->pos[X]] == '1')
			break ;
	}
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
	short		x;
	short		width;
	t_array		r;
	t_wall		wall;

	x = -1;
	width = (short)G->img->width;
	while (++x < width)
	{
		r.camx = (2.0 * (double)x / (double)width - 1.0);
		r.dir[X] = G->vec[1].x + (G->vec[2].x * r.camx);
		r.dir[Y] = G->vec[1].y + (G->vec[2].y * r.camx);
		r.dir_dis[X] = fabs(1.0 / r.dir[X]);
		r.dir_dis[Y] = fabs(1.0 / r.dir[Y]);
		r.pos[X] = G->vec[0].x;
		r.pos[Y] = G->vec[0].y;
		if (r.dir[X] < 0)
			dirxl(&r, G->vec);
		else
			dirxr(&r, G->vec);
		if (r.dir[Y] < 0)
			diryu(&r, G->vec);
		else
			diryd(&r, G->vec);
		wall.hit_ax = cast_ray2(&r, map);
		d_collision(&r, &wall);
		walls(&wall, x, G, &r);
	}
}
