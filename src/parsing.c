/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:19:03 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/04 15:45:00 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*Reads the contents of the map file into 
  memory an stores them in a structred format */

void	get_raw(char *file, t_map *map_data)
{
	int		fd;
	char	*content;

	if (ft_strlen(file) < 5 || \
		ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
	{
		ft_error("Invalid file extension");
		exit(EXIT_FAILURE);
	}
	open_file(file, &fd, &content);
	map_data->raw = ft_split(ft_strtrim(content, " \n"), '\n');
	free(content);
}
/*function that verifies that all required keys are present in the map file*/

void	check_params(t_map *map_data, char params[6][4])
{
	unsigned short	i;
	unsigned short	j;
	bool			key_found[6];

	ft_bzero(key_found, sizeof(bool) * 6);
	i = -1;
	while (map_data->raw[++i] != NULL)
	{
		j = -1;
		while (++j < 6)
		{
			if (ft_strncmp(map_data->raw[i], params[j], 2) == 0)
			{
				if (key_found[j])
					ft_error("Key appears more than once.\n");
				else
					key_found[j] = true;
			}
		}
	}
	i = 0;
	while (i < 6)
		if (!key_found[i++])
			ft_error("Missing key.\n");
}

/*Parses and extracts texture paths from the map file.*/

void	get_textures_path(t_map *map_data, char paths[4][4])
{
	unsigned short	i;
	unsigned short	j;
	char			**tmp;

	i = -1;
	while (map_data->raw[++i] != NULL)
	{
		j = -1;
		while (++j < 4)
		{
			if (ft_strncmp(map_data->raw[i], paths[j], 3) == 0)
			{
				tmp = ft_split(map_data->raw[i], ' ');
				if (tmp != NULL && tmp[1] != NULL)
				{
					map_data->texture[j] = ft_strdup(tmp[1]);
					ft_free(tmp);
				}
				else
					ft_error("Error: Texture path not found.\n");
			}
		}
	}
}
/*Extracts floor and ceiling colors from the map file.*/

void	get_rgb(t_map *map_data)
{
	unsigned short	i;
	short			*array;
	char			**tmp[2];

	i = 0;
	while (map_data->raw[i])
	{
		array = NULL;
		if (ft_strncmp(map_data->raw[i], "F ", 2) == 0)
			array = map_data->floor;
		else if (ft_strncmp(map_data->raw[i], "C ", 2) == 0)
			array = map_data->ceil;
		if (array != NULL)
		{
			tmp[0] = ft_split(map_data->raw[i], ' ');
			if (tmp[0] && tmp[0][1])
			{
				tmp[1] = ft_split(tmp[0][1], ',');
				if (tmp[1] && tmp[1][0] && tmp[1][1] && tmp[1][2])
				{
					array[0] = ft_atoi(tmp[1][0]);
					array[1] = ft_atoi(tmp[1][1]);
					array[2] = ft_atoi(tmp[1][2]);
				}
			}
			ft_free(tmp[0]);
			ft_free(tmp[1]);
		}
		i++;
	}
}

/*function  to check for valid rgb color*/

void	check_valid_rgb(t_map *map_data)
{
	unsigned short	i;

	i = 0;
	while (i < 3)
	{
		if ((map_data->floor[i] < 0 || map_data->floor[i] > 255))
			ft_error("Invalid color range!\n");
		if ((map_data->ceil[i] < 0 || map_data->ceil[i] > 255))
			ft_error("Invalid color range!\n");
		i++;
	}
}
