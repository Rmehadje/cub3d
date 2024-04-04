/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:32:45 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/04 15:41:09 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1920
# define FOV 0.66
# define HEIGHT 1080
# define WALK 0.2
# define ROT 0.2
# include <unistd.h>
# include "../libft/libft/libft.h"
# include <stdio.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdbool.h>


enum e_vectors
{
	POS = 0,
	DIR = 1,
	CAM = 2
};

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_map
{
	char			**map;
	char			**raw;
	char			*texture[4];
	short			floor[3];
	short			ceil[3]; 
	unsigned short	height;
	unsigned short	width;
}	t_map;


typedef struct s_game_data
{
	t_vec	vectors[3];
	// mlx_t		*mlx;
	// mlx_image_t		*img;
	// mlx_texture_t	*walls;
	t_map		map_data;	
}	t_game_data;


typedef struct s_texture
{
	int		height;
	int		width;
	int		end;
	int		start;
	int		wall_x;
	double	step;
	double	pos;
	int		pix[2];
} t_texture;

typedef struct s_general
{
	t_vec		vec[3];
	mlx_t		*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*walls[4];
	int	floorcolor[3];
	int	ceilingcolor[3];
	t_map		*map;
}	t_general;

typedef struct s_wall
{
	double	wall_dist;
	int		wall_hit;
	int		hit_ax;
} t_wall;

typedef	struct	s_array
{
	double	dir[2];
	double	dir_dis[2];
	double	step_dis[2];
	double	camx;
	int	s[2];
	int	h_side[2];
	int	pos[2];
	int	haxis;
}	t_array;

enum	e_XandY
{
	X = 0,
	Y = 1
};

//utils
void	ft_error(char *str);
void	open_file(char *file, int *fd, char **content);
void	ft_free(char **str);
//parsing
void	get_raw(char *file, t_map *map_data);
void	check_params(t_map	*map_data, char params[6][4]);
void	get_textures_path(t_map *map_data, char paths[4][4]);
void	check_valid_rgb(t_map *map_data);
short	get_begin_and_end(t_map *map_data);
void	check_if_open(t_map *map_data);
void	get_map(t_map *map_data, short begin, short end);
void	get_player(t_map *map_data, t_game_data *game_data);

void	Gunit(t_general *G, t_map	*map);
void	setmap(t_general *G, t_map *map);
void	check_pos(t_general *G, char **map);
void	player_direction(t_general *G, char flag);
int32_t	ft_pixel(int32_t	r, int32_t g, int32_t b, int32_t a);
void	ceiling_and_floor(t_general *G);
void	texture_path(t_map *map);
int	cast_ray2(t_array *r, char **map);
void	d_collision(t_array *r, t_wall *wall);
void	cast_ray(t_general *G, char **map);
void	rotation(t_vec *vec, short sign);
void	movement(t_general *G, t_vec *vec);	
void	dirxL(t_array	*r, t_vec	*vec);
void	dirxR(t_array	*r, t_vec	*vec);
void	diryu(t_array	*r, t_vec	*vec);
void	diryd(t_array	*r, t_vec	*vec);
void	walls(t_wall *wall, short x, t_general *G, t_array *r);
void	set_texture(t_texture *t, t_wall *wall, mlx_texture_t *text, t_array *r);
void	texture(t_texture *t, t_wall *wall, t_general *G, t_array *r);
void	keyhooks(mlx_key_data_t	keydata, void *param);








#endif