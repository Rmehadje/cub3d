/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:14:41 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/04 15:45:24 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// function to get the  beginning of the  map and his ending

short	get_begin_and_end(t_map *map_data)
{
	unsigned short	i;
	unsigned short	j;
	int				found_one;

	i = 0;
	while (map_data->raw[i])
	{
		j = 0;
		found_one = 0;
		while (map_data->raw[i][j] == ' ' || map_data->raw[i][j] == '1')
		{
			if (found_one == 0 && map_data->raw[i][j] == '1')
				found_one = 1;
			j++;
		}
		if (found_one == 1 && map_data->raw[i][j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
// Check for openings at the start and end of each row
// Check for openings in the middle of the map

void	check_if_open(t_map *map_data)
{
    int i;
	int j;
    bool found_one;

	i = 0;
    while (++i < map_data->height)
    {
        found_one = (map_data->map[i][0] == '1' 
				&& map_data->map[i][ft_strlen(map_data->map[i]) - 1] == '1');
        if (!found_one)
			ft_error("Map error\n");
    }
	i = 1;
    while (i++ < map_data->height - 1)
    {
		j = 1;
        while (j++ < (int)ft_strlen(map_data->map[i]) - 1)
        {
            if (map_data->map[i][j] == '0')
                if (map_data->map[i - 1][j] == ' ' ||
                    map_data->map[i][j - 1] == ' ' ||
                    map_data->map[i + 1][j] == ' ' ||
                    map_data->map[i][j + 1] == ' ')
						ft_error("Map error\n");
        }
    }
}
/* 
	function to extract the map data from the raw 
	input based on begin and end indices, it processes the map data according 
	to the specified rules and stores it in the provided data structure
*/
void get_map(t_map *map_data, short begin, short end)
{
	short i;

	if (begin == -1 || end == -1)
		ft_error("Invalid map\n");
	map_data->height = end - begin + 1;
	map_data->map = ft_calloc(map_data->height + 1, sizeof(char *));
	if (!map_data->map)
		ft_error("Memory allocation failed\n");
	map_data->width = 0;
	i = begin;
	while(i <= end)
	{
		if (map_data->width < ft_strlen(map_data->raw[i]))
			map_data->width = ft_strlen(map_data->raw[i]);
		i++;
	}
	i = begin;
	while (i <= end)
	{
		map_data->map[i - begin] = ft_strdup(map_data->raw[i]);
		i++;
	}
}

void	set_vectors(char dir, t_game_data *game_data)
{
	if (dir == 'N')
	{
		game_data->vectors[DIR] = (t_vec){0, -1};
		game_data->vectors[CAM] = (t_vec){FOV, 0};
	}
	else if (dir == 'S')
	{
		game_data->vectors[DIR] = (t_vec){0, 1};
		game_data->vectors[CAM] = (t_vec){FOV * -1, 0};
	}
	else if (dir == 'E')
	{
		game_data->vectors[DIR] = (t_vec){-1, 0};
		game_data->vectors[CAM] = (t_vec){0, FOV * -1};
	}
	else
	{
		game_data->vectors[DIR] = (t_vec){1, 0};
		game_data->vectors[CAM] = (t_vec){0, FOV};
	}
}

/*
	it checks each character in the map for player symbols ('N', 'S', 'E', 'W')
	or invalid characters, similar to the previous implementation.

	**still having a bus error!!!**
*/
void	get_player(t_map *map_data, t_game_data *game_data)
{
	unsigned short	x;
	unsigned short	y;

	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			char symbol = map_data->map[y][x];
			if (ft_strchr("NSEW", symbol))
			{
				if (game_data->vectors[0].x != 0 && game_data->vectors[0].y != 0)
					ft_error("Only one player allowed!");
				game_data->vectors[0].x = (double)x + 0.5;
				game_data->vectors[0].y = (double)y + 0.5;
				set_vectors(symbol, game_data);
				map_data->map[y][x] = '0';
			}
			else if (symbol != '0' && symbol != '1' && symbol != ' ')
				ft_error("Invalid character in map!");
			x++;
		}
		y++;
	}
}

// int main() {
//     // Mock map data
//     char *map[] = {
//         "111111",
//         "1000W1",
//         "101011",
//         "1S0001",
//         "111111",
//         NULL
//     };
//     t_map_data map_data;
//     map_data.map = map;
//     map_data.height = 5; // Height of the map

//     // Initialize game data
//     t_game_data game_data = {
//         .vectors = {{0}, {0}} // Initialize vectors to zero
//     };

//     // Call the get_player function
//     get_player(&map_data, &game_data);

//     // Print the player's position for testing
//     printf("Player position: (%.1f, %.1f)\n", game_data.vectors[0].x, game_data.vectors[0].y);

//     return 0;
// }