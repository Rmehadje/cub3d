/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:14:41 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/29 15:03:17 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// function to get the  beginning of the  map and his ending

int	get_first(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' && str[i + 1] == '1')
			return (0);
		i++;
	}
	return (1);
}

int get_begin(char **raw)
{
	int         	i;
	int         	j;
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
	while (raw[i])
	{
		if (get_first(raw[i]) == 0)
			break ;
		i++;
	}
	return (i);
}
int	get_end(char **raw)
{
	int         	i;
	int         	j;
	//int				found_one;
	
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
            if(raw[i][j] != ' ' || raw[i][j] != '\n' ||
                (raw[i][j] != '\t') || raw[i][j] != '\0')
                j++;
        }
        i--;
	}
	return (i);
}

// Check for openings at the start and end of each row  
// Check for openings in the middle of the map
void check_if_open(t_map *map_data) 
{
    int i;
    size_t j;
    char *line;
    char *trimmed_line;
    bool has_one;
    // Vérification des premières et dernières colonnes de chaque ligne
    i = 0;
	 has_one = false;
    while (i < map_data->height)
    {
        line = ft_strdup(map_data->map[i]);
        trimmed_line = ft_strtrim(line, " ");
		  if (trimmed_line[0] == '1' && (trimmed_line[ft_strlen(trimmed_line) - 2] == '1' ||
		  	 trimmed_line[ft_strlen(trimmed_line) - 2] == '\n'))
				has_one = true;
			else
				has_one = false;
        free(line);
        if (!has_one){
		    ft_error("Error Opening\n");
        }
        i++;
    }
    // Vérification des cases adjacentes à '0'
	 
    i = 1;
    while (i < map_data->height - 1)
    {
        j = 1;
        while (j <= ft_strlen(map_data->map[i]))
        {
            if (map_data->map[i][j] == '0' &&
                (map_data->map[i - 1][j] == ' ' ||
                 map_data->map[i][j - 1] == ' ' ||
                 map_data->map[i + 1][j] == ' ' ||
                 map_data->map[i][j + 1] == ' ')) {
		         ft_error("Error Opening\n");
            }
            j++;
        }
        i++;
    }
}

/* 
	function to extract the map data from the raw 
	input based on begin and end indices, it processes the map data according 
	to the specified rules and stores it in the provided data structure
*/

int get_map(char **raw,t_map *map_data, int begin, int end)
{
	short i;
	if (begin == -1 || end == -1)
	{
		ft_error("Invalid map\n");
		return (-1);
	}
	map_data->height = (end - begin) + 1;
	map_data->map = ft_calloc(map_data->height + 1, sizeof(char *));
	if (!map_data->map)
		ft_error("Memory allocation failed\n");
	i = 0;
	while (begin <= end)
	{
		map_data->map[i] = ft_strdup(raw[begin]);
		begin++;
		i++;
	}
   return 1;
}

// void	set_vectors(char dir, t_game_data *game_data)
// {
// 	if (dir == 'N')
// 	{
// 		game_data->vectors[DIR] = (t_vec){0, -1};
// 		game_data->vectors[CAM] = (t_vec){FOV, 0};
// 	}
// 	else if (dir == 'S')
// 	{
// 		game_data->vectors[DIR] = (t_vec){0, 1};
// 		game_data->vectors[CAM] = (t_vec){FOV * -1, 0};
// 	}
// 	else if (dir == 'E')
// 	{
// 		game_data->vectors[DIR] = (t_vec){-1, 0};
// 		game_data->vectors[CAM] = (t_vec){0, FOV * -1};
// 	}
// 	else
// 	{
// 		game_data->vectors[DIR] = (t_vec){1, 0};
// 		game_data->vectors[CAM] = (t_vec){0, FOV};
// 	}
// }

/*
	it checks each character in the map for player symbols ('N', 'S', 'E', 'W')
	or invalid characters, similar to the previous implementation.
*/
// void	get_player(t_map *map_data)
// {
// 	unsigned short	x;
// 	unsigned short	y;
// 	char 			symbol;

// 	y = 0;
// 	while (map_data->map[y])
// 	{
// 		x = 0;
// 		while (map_data->map[y][x])
// 		{
// 			symbol = map_data->map[y][x];
// 			if (ft_strchr("NSEW", symbol))
// 			{
// 				if (map_data->vectors[0].x != 0 && map_data->vectors[0].y != 0)
// 					ft_error("Only one player allowed!\n");
// 				map_data->vectors[0].x = (double)x + 0.5;
// 				map_data->vectors[0].y = (double)y + 0.5;
// 				set_vectors(symbol, map_data);
// 				map_data->map[y][x] = '0';
// 			}
// 			else if (symbol != '0' && symbol != '1' && symbol != ' ' && symbol != '\t' && symbol != '\n')
// 				ft_error("Invalid character in map!\n");
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	check_pp2(char **map, t_vector player_pos)
// {
// 	t_map_data *map_data;
// 	int i = 0;
// 	int j = 0;

// 	while (map[i])
// 	{
// 		if (only_spaces(map[i]))
// 		{
// 			if (player_pos.y > i)
// 			{
// 				if (!only_spaces(map[i]))
// 					remake_map(map_data, get_begin(), get_end())
// 			}
// 			else
				
// 		}
// 	}
// }
// int remake_map()
