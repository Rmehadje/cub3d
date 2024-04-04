/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:13:18 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/04 16:58:23 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main (int argc, char **argv)
{
	t_general G;
	t_map		map;
(void)argv;
	if (argc == 1)
	{
		Gunit(&G, &map);
		
	}
	free(&G);
	free(&map);
	return (EXIT_SUCCESS);
}
