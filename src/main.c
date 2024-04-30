/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:13:18 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 20:51:46 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_general		g;
	t_map			map;
	int				i;

	g.img = NULL;
	g.mlx = NULL;
	i = -1;
	while (++i < 4)
	{
		g.walls[i] = NULL;
		map.texture[i] = NULL;
	}
	if (argc != 2)
		ft_error("Wrong number of argument", NULL, NULL, 0);
	else
		if (parser((char *)argv[1], &map) == -1)
			ft_error("parsing error", NULL, NULL, 0);
	gunit(&g, &map);
	return (EXIT_SUCCESS);
}
