/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:23:28 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 17:06:20 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
