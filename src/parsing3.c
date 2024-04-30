/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:16:48 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 18:35:13 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// function to get the  beginning of the  map and his ending

int	get_first(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' && str[i + 1] == '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_chars(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != 'W' &&
				map[i][j] != 'N' && map[i][j] != '1' && map[i][j] != '0' &&
				map[i][j] != ' ' && map[i][j] != '\n')
				return (1);
		}
	}
	return (0);
}

void	check_f_l(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[0][++i])
	{
		if (map[0][i] != '1' && map[0][i] != '\n')
			return (ft_free(map), ft_error("Error opening", NULL, NULL, 0));
	}
	while (map[++j])
		;
	j--;
	i = -1;
	while (map[j][++i])
	{
		if (map[j][i] != '1' && map[j][i] != '\n')
			return (ft_free(map), ft_error("Error opening", NULL, NULL, 0));
	}
}
/*function  to check for valid rgb color*/

void	check_valid_rgb(t_map *map_data)
{
	unsigned short	i;

	i = 0;
	while (i < 3)
	{
		if (!(map_data->floor[i] >= 0 && map_data->floor[i] <= 255))
			ft_error("Invalid color range for floor!\n", NULL, map_data, 1);
		if (!(map_data->ceil[i] >= 0 && map_data->ceil[i] <= 255))
			ft_error("Invalid color range for ceiling!\n", NULL, map_data, 1);
		i++;
	}
}

/* 
	function to extract the map data from the raw 
	input based on begin and end indices, it processes the map data according 
	to the specified rules and stores it in the provided data structure
*/

int	get_map(char **raw, t_map *map_data, int begin, int end)
{
	short	i;

	if (begin == -1 || end == -1)
	{
		ft_error("Invalid map\n", NULL, map_data, 1);
		return (-1);
	}
	map_data->height = (end - begin) + 1;
	map_data->map = ft_calloc(map_data->height + 1, sizeof(char *));
	if (!map_data->map)
		ft_error("Memory allocation failed\n", NULL, map_data, 1);
	i = 0;
	while (begin <= end)
	{
		map_data->map[i] = ft_strdup(raw[begin]);
		begin++;
		i++;
	}
	return (1);
}
