/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:19:03 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 16:39:17 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*Reads the contents of the map file into 
  memory an stores them in a structred format */

char	**get_raw(char *file)
{
	int			fd;
	int			i;
	char		**raw;

	i = 0;
	if (ft_strlen(file) < 5 || \
		ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
	{
		ft_error("Invalid file extension");
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_RDONLY);
	raw = (char **)ft_calloc(1000, sizeof(char *));
	while (true)
	{
		raw[i] = get_next_line(fd);
		if (raw[i] == NULL)
			break ;
		i++;
	}
	close(fd);
	return (raw);
}
/*function that verifies that all required keys are present in the map file*/

void	check_params(char **raw, char params[6][4])
{
	unsigned short	it[2];
	bool			key_found[6];

	ft_bzero(key_found, sizeof(bool) * 6);
	it[0] = 0;
	while (raw[it[0]] != NULL)
	{
		it[1] = 0;
		while (it[1] < 6)
		{
			if (ft_strncmp(raw[it[0]], params[it[1]], 2) == 0)
			{
				if (key_found[it[1]])
					ft_error("Key appears more than once.\n");
				else
					key_found[it[1]] = true;
			}
			it[1]++;
		}
		it[0]++;
	}
	it[0] = 0;
	while (it[0] < 6)
		if (!key_found[it[0]++])
			ft_error("Missing key.\n");
}

/*Parses and extracts texture paths from the map file.*/

void	get_textures_path(char **raw, t_map *map_data, char paths[4][4])
{
	int				i;
	int				j;
	char			**tmp;

	i = 0;
	while (raw[i] != NULL)
	{
		j = 0;
		while (j < 4)
		{
			if (ft_strncmp(raw[i], paths[j], 3) == 0)
			{
				tmp = ft_split(raw[i], ' ');
				if (tmp != NULL && tmp[1] != NULL)
				{
					map_data->texture[j] = ft_strdup2(tmp[1]);
					ft_free(tmp);
				}
				else
					ft_error("Error: Texture path not found.\n");
			}
			j++;
		}
		i++;
	}
}
/*Extracts floor and ceiling colors from the map file.*/

void	parse_rgb_line(char *line, short *array)
{
	char	**tmp;
	char	**value;

	tmp = ft_split(line, ' ');
	if (!tmp || !tmp[1])
		return ;
	value = ft_split(tmp[1], ',');
	ft_free(tmp);
	if (!value || !value[0] || !value[1] || !value[2])
	{
		ft_free(value);
		return ;
	}
	array[0] = ft_atoi(value[0]);
	array[1] = ft_atoi(value[1]);
	array[2] = ft_atoi(value[2]);
	ft_free(value);
}
/*Extracts floor and ceiling colors from the map file.*/

void	get_rgb(char **raw, t_map *map_data)
{
	unsigned short	i;
	short			*array;

	i = 0;
	while (raw[i])
	{
		array = NULL;
		if (ft_strncmp(raw[i], "F ", 2) == 0)
			array = map_data->floor;
		else if (ft_strncmp(raw[i], "C ", 2) == 0)
			array = map_data->ceil;
		if (array != NULL)
			parse_rgb_line(raw[i], array);
		i++;
	}
}
