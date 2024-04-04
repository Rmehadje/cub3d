/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:47:12 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/04 16:22:09 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	setmap(t_general *G, t_map *map)
{
	G->walls[0] = mlx_load_png(map->texture[0]);
	G->walls[1] = mlx_load_png(map->texture[1]);
	G->walls[2] = mlx_load_png(map->texture[2]);
	G->walls[3] = mlx_load_png(map->texture[3]);
}
void	player_direction(t_general *G, char flag)
{
	if (flag == 'N')
	{
		G->vec[1] = (t_vec){0, -1};
		G->vec[1] = (t_vec){FOV, 0};
	}
	else if (flag == 'E')
	{
		G->vec[1] = (t_vec){-1, 0};
		G->vec[1] = (t_vec){0, FOV * -1};
	}
	else if (flag == 'W')
	{
		G->vec[1] = (t_vec){1, 0};
		G->vec[1] = (t_vec){0, FOV};
	}
	else
	{
		G->vec[1] = (t_vec){0, 1};
		G->vec[1] = (t_vec){FOV * -1, 0};
	}
}

void	check_pos(t_general *G, char **map)
{
	int	x;
	int	y;
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
				G->vec[0].x = (double)x + 0.5;
				G->vec[0].y = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
	player_direction(G, flag);
}

void	keyhooks(mlx_key_data_t	keydata, void *param)
{
	t_general *G;

	G = (t_general *)param;
	ceiling_and_floor(G);
	cast_ray(G, G->map->map);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(G->mlx);
		exit(0);
	}
	if (mlx_is_key_down(G->mlx, MLX_KEY_RIGHT))
		rotation(G->vec, 1);
	if (mlx_is_key_down(G->mlx, MLX_KEY_RIGHT))
		rotation(G->vec, -1);
	movement(G, G->vec);
}

void	Gunit(t_general *G, t_map	*map)
{
	setmap(G, map);
	G->map = map;
	check_pos(G, G->map->map);
	G->mlx = NULL;
	G->img = NULL;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	G->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", 1);
	if (!G->mlx)
		return ;
	G->img = mlx_new_image(G->mlx, WIDTH, HEIGHT);
	if(!G->img)
		return ;
	mlx_image_to_window(G->mlx, G->img, 0, 0);
	ceiling_and_floor(G);
	cast_ray(G, G->map->map);
	mlx_key_hook(G->mlx, &keyhooks, G);
	mlx_loop(G->mlx);
	mlx_terminate(G->mlx);
}
