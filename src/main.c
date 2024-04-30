/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:13:18 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 17:04:42 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_general		g;
	t_map			map;

	atexit(leaks);
	if (argc != 2)
	{
		ft_error("Wrong number of argument\n");
		return (0);
	}
	else
	{
		if (parser((char *)argv[1], &map) == -1)
			printf("parsing error\n");
	}
	gunit(&g, &map);
	return (EXIT_SUCCESS);
}
