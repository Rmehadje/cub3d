/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:01:03 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 14:55:24 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(t_general *G, t_vec *vec)
{
	double		w_x;
	double		w_y;

	w_x = vec[1].x * WALK;
	w_y = vec[1].y * WALK;
	if (mlx_is_key_down(G->mlx, MLX_KEY_D))
		if (G->map->map[(int)(vec[0].y + w_x)][(int)(vec[0].x - w_y)] != '1')
			vec[0] = (t_vec){vec[0].x - w_y, vec[0].y + w_x};
	if (mlx_is_key_down(G->mlx, MLX_KEY_A))
		if (G->map->map[(int)(vec[0].y - w_x)][(int)(vec[0].x + w_y)] != '1')
			vec[0] = (t_vec){vec[0].x + w_y, vec[0].y - w_x};
	if (mlx_is_key_down(G->mlx, MLX_KEY_W))
		if (G->map->map[(int)(vec[0].y + w_y)][(int)(vec[0].x + w_x)] != '1')
			vec[0] = (t_vec){vec[0].x + w_x, vec[0].y + w_y};
	if (mlx_is_key_down(G->mlx, MLX_KEY_S))
		if (G->map->map[(int)(vec[0].y - w_y)][(int)(vec[0].x - w_x)] != '1')
			vec[0] = (t_vec){vec[0].x - w_x, vec[0].y - w_y};
}

void	rotation(t_vec *vec, short sign)
{
	double	ca;	
	double	sa;
	double	tmp;

	ca = cos(sign * ROT);
	sa = sin(sign * ROT);
	tmp = vec[1].x;
	vec[1].x = (vec[1].x * ca) - (vec[1].y * sa);
	vec[1].y = (tmp * sa) + (vec[1].y * ca);
	tmp = vec[2].x;
	vec[2].x = (vec[2].x * ca) - (vec[2].y * sa);
	vec[2].y = (tmp * sa) + (vec[2].y * ca);
}
