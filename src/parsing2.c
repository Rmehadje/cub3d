/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobadiah <mobadiah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:14:41 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 16:40:39 by mobadiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	find_next_condition(char **raw, int start_index)
{
	int	i;

	i = start_index;
	while (raw[i])
	{
		if (get_first(raw[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	get_begin(char **raw)
{
	int				i;
	int				j;
	int				flag;

	i = -1;
	flag = 0;
	while (raw[++i])
	{
		j = -1;
		while (raw[i][++j])
		{
			if (raw[i][j] == 'C')
			{
				flag = 1;
				break ;
			}
		}
		if (flag)
			break ;
	}
	i++;
	return (find_next_condition(raw, i));
}

int	get_end(char **raw)
{
	int				i;
	int				j;

	i = 0;
	while (raw[i])
		i++;
	i--;
	j = 0;
	while (raw[i])
	{
		j = 0;
		while (raw[i][j])
		{
			if (ft_isdigit(raw[i][j]) == '1')
				return (i);
			if (raw[i][j] != ' ' || raw[i][j] != '\n' ||
				(raw[i][j] != '\t') || raw[i][j] != '\0')
				j++;
		}
		i--;
	}
	return (i);
}

// Check for openings at the start and end of each row  
// Check for openings in the middle of the map

void	check_if_open_helper(t_map *map_data, int start_index)
{
	int	i;
	int	j;

	i = start_index;
	while (i < map_data->height - 1)
	{
		j = 1;
		while (j <= ft_strlen(map_data->map[i]))
		{
			if (map_data->map[i][j] == '0' &&
				(map_data->map[i - 1][j] == ' ' ||
					map_data->map[i][j - 1] == ' ' ||
					map_data->map[i + 1][j] == ' ' ||
					map_data->map[i][j + 1] == ' '))
			{
				ft_error("Error Opening\n");
			}
			j++;
		}
		i++;
	}
}

void	check_if_open(t_map *map_data)
{
	int		i;
	int		j;
	char	*line;
	char	*t_l;
	bool	has_one;

	i = 0;
	has_one = false;
	while (i < map_data->height)
	{
		line = ft_strdup(map_data->map[i]);
		t_l = ft_strtrim(line, " ");
		if (t_l[0] == '1' && (t_l[ft_strlen(t_l) - 2] == '1'
				|| t_l[ft_strlen(t_l) - 2] == '\n'))
			has_one = true;
		else
			has_one = false;
		free(line);
		if (!has_one)
			ft_error("Error Opening\n");
		i++;
	}
	check_if_open_helper(map_data, 1);
}
