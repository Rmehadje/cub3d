/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:12 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 18:48:44 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	setmap(t_general *g, t_map *map)
{
	g->walls[0] = mlx_load_png(map->texture[0]);
	g->walls[1] = mlx_load_png(map->texture[1]);
	g->walls[2] = mlx_load_png(map->texture[2]);
	g->walls[3] = mlx_load_png(map->texture[3]);
}

void	player_direction(t_general *g, char flag)
{
	if (flag == 'N')
	{
		g->vec[1] = (t_vec){0.0, -1.0};
		g->vec[2] = (t_vec){FOV, 0.0};
	}
	else if (flag == 'E')
	{
		g->vec[1] = (t_vec){-1.0, 0.0};
		g->vec[2] = (t_vec){0.0, FOV * -1.0};
	}
	else if (flag == 'W')
	{
		g->vec[1] = (t_vec){1.0, 0.0};
		g->vec[2] = (t_vec){0.0, FOV};
	}
	else
	{
		g->vec[1] = (t_vec){0.0, 1.0};
		g->vec[2] = (t_vec){FOV * -1.0, 0.0};
	}
}

void	check_pos(t_general *g, char **map)
{
	int		x;
	int		y;
	char	flag;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
					|| map[y][x] == 'W' || map[y][x] == 'S')
			{
				flag = map[y][x];
				g->vec[0].x = (double)x + 0.5;
				g->vec[0].y = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
	player_direction(g, flag);
}

void	keyhooks(void *param)
{
	t_general	*g;

	g = (t_general *)param;
	ceiling_and_floor(g);
	cast_ray(g, g->map->map);
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		ft_error("quitina", g, g->map, 1);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		rotation(g->vec, 1);
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		rotation(g->vec, -1);
	movement(g, g->vec);
}

void	gunit(t_general *g, t_map *map)
{
	setmap(g, map);
	g->map = map;
	check_pos(g, g->map->map);
	g->mlx = NULL;
	g->img = NULL;
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	g->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!g->mlx)
		return ;
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img)
		return ;
	mlx_image_to_window(g->mlx, g->img, 0, 0);
	ceiling_and_floor(g);
	cast_ray(g, g->map->map);
	mlx_loop_hook(g->mlx, keyhooks, g);
	mlx_loop(g->mlx);
	mlx_terminate(g->mlx);
}
