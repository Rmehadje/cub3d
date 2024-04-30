/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:16:48 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 14:38:08 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
				map[i][j] != 'N' && map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != '\n')
					return (1);
		}
	}
	return (0);
}

int	parser(char *file, t_map *map_data)
{
	char	**raw;

	raw = get_raw(file);
	check_params(raw, (char [6][4]){"NO ", "SO ", "EA ", "WE ", "C ", "F "});
	get_textures_path(raw, map_data, (char [4][4]){"NO ", "SO ", "EA ", "WE "});
	get_rgb(raw, map_data);
	check_valid_rgb(map_data);
	if (get_map(raw, map_data, get_begin(raw), get_end(raw)) == -1)
		return (-1);
	ft_free(raw);
	if (check_chars(map_data->map) == 1)
		return (-1);
	check_if_open(map_data);
	check_f_l(map_data->map);
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
			ft_error("Error opening");
	}
	while (map[++j])
		;
	j--;
	i = -1;
	while (map[j][++i])
	{
		if (map[j][i] != '1' && map[j][i] != '\n')
			ft_error("Error opening");
	}
}