/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:23:28 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 21:10:52 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parser(char *file, t_map *map_data)
{
	char	**raw;
	int		check;

	check = 0;
	raw = get_raw(file);
	check_params(raw, (char [6][4]){"NO ", "SO ", "EA ", "WE ", "C ", "F "});
	get_textures_path(raw, map_data, (char [4][4]){"NO ", "SO ", "EA ", "WE "});
	check = get_rgb(raw, map_data);
	if (check == -1)
		return (ft_free2(raw), ft_error("", NULL, map_data, 1), 0);
	else if (check == -2)
		return (ft_free2(raw), ft_error("wrong\n", NULL, NULL, 0), 0);
	check_valid_rgb(map_data);
	if (get_map(raw, map_data, get_begin(raw), get_end(raw)) == -1)
		return (-1);
	ft_free2(raw);
	if (check_chars(map_data->map) == 1)
		return (-1);
	check_if_open(map_data);
	check_f_l(map_data->map);
	return (0);
}

int	get_rgb(char **raw, t_map *map_data)
{
	unsigned short	i;
	short			*array;
	int				k;

	k = 0;
	i = 0;
	while (raw[i])
	{
		array = NULL;
		if (ft_strncmp(raw[i], "F ", 2) == 0)
			array = map_data->floor;
		else if (ft_strncmp(raw[i], "C ", 2) == 0)
			array = map_data->ceil;
		if (array != NULL)
		{
			k = parse_rgb_line(raw[i], array);
			if (k < 0)
				return (k);
		}
		i++;
	}
	return (0);
}
