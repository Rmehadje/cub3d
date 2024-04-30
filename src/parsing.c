/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:19:03 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 21:10:59 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**get_raw(char *file)
{
	int			fd;
	int			i;
	char		**raw;
	char		*ptr;

	i = 0;
	if (ft_strlen(file) < 5 || \
		ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		ft_error("Invalid file extension", NULL, NULL, 0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("ERROR: INVALID FILE", NULL, NULL, 0);
	raw = (char **)ft_calloc(1000, sizeof(char *));
	while (true)
	{
		ptr = get_next_line(fd);
		if (ptr == NULL)
			break ;
		else
			raw[i] = ptr;
		i++;
	}
	raw[999] = NULL;
	close(fd);
	return (raw);
}

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
					return (ft_free2(raw), ft_error("error.\n", NULL, NULL, 0));
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
			return (ft_free2(raw), ft_error("Missing key.\n", NULL, NULL, 0));
}

void	get_textures_path(char **raw, t_map *map_data, char paths[4][4])
{
	int				i;
	int				j;
	char			**tmp;

	i = -1;
	while (raw[++i] != NULL)
	{
		j = -1;
		while (++j < 4)
		{
			if (ft_strncmp(raw[i], paths[j], 3) == 0)
			{
				tmp = ft_split(raw[i], ' ');
				if (tmp != NULL && tmp[1] != NULL)
				{
					map_data->texture[j] = ft_strdup2(tmp[1]);
					ft_free2(tmp);
				}
				else
					return (ft_free2(raw), ft_error(
							"Error: Texture path not found.\n",
							NULL, map_data, 1));
			}
		}
	}
}

static void	fill_vec(short *array, char **value)
{
	array[0] = ft_atoi(value[0]);
	array[1] = ft_atoi(value[1]);
	array[2] = ft_atoi(value[2]);
}

int	parse_rgb_line(char *line, short *array)
{
	char	**tmp;
	char	**value;
	int		k;
	int		i;
	char	*r;

	tmp = ft_split(line, ' ');
	if (!tmp || !tmp[1])
		return (-1);
	value = ft_split(tmp[1], ',');
	ft_free2(tmp);
	if (!value || !value[0] || !value[1] || !value[2])
		return (ft_free2(value), -1);
	r = ft_strdup2(value[2]);
	free(value[2]);
	value[2] = r;
	i = -1;
	while (value[++i])
	{
		k = -1;
		while (value[i][++k])
			if (!ft_isdigit(value[i][k]))
				return (ft_free2(value), -2);
	}
	return (fill_vec(array, value), ft_free2(value), 0);
}
