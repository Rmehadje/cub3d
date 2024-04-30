/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:32:45 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/30 21:11:46 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1920
# define FOV 0.66
# define HEIGHT 1080
# define WALK 0.04
# define ROT 0.04
# include <unistd.h>
# include "../libft/libft.h"
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
	char			*texture[4];
	short			floor[3];
	short			ceil[3];
	unsigned short	height;
	unsigned short	width;
}	t_map;

typedef struct s_texture
{
	int		height;
	int		width;
	int		end;
	int		start;
	double	wall_x;
	double	step;
	double	pos;
	int		pix[2];
}	t_texture;

typedef struct s_general
{
	t_vec			vec[3];
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*walls[4];
	t_map			*map;
}	t_general;

typedef struct s_wall
{
	double	wall_dist;
	int		wall_hit;
	int		hit_ax;
}	t_wall;

typedef struct s_array
{
	double	dir[2];
	double	dir_dis[2];
	double	step_dis[2];
	double	camx;
	int		s[2];
	int		h_side[2];
	int		pos[2];
	int		haxis;
}	t_array;

enum	e_XandY
{
	X = 0,
	Y = 1
};

//utils
void	ft_error(char *msg, t_general *g, t_map *m, int flag);
void	open_file(char *file, int *fd, char **content);
void	ft_free(char **str);
//parsing
char	**get_raw(char *file);
void	check_params(char **raw, char params[6][4]);
void	get_textures_path(char **raw, t_map *map_data, char paths[4][4]);
int		parse_rgb_line(char *line, short *array);
int		get_rgb(char **raw, t_map *map_data);
void	check_valid_rgb(t_map *map_data);
int		get_first(char *str);
int		get_begin(char **raw);
int		get_end(char **raw);
int		get_map(char **raw, t_map *map_data, int begin, int end);
int		check_chars(char **map);
void	check_f_l(char **map);
void	check_if_open(t_map *map_data);
int		parser(char *file, t_map *map_data);
char	*ft_strdup2(const char *s1);
void	ft_free2(char **str);

//execution
void	gunit(t_general *g, t_map	*map);
void	setmap(t_general *G, t_map *map);
void	check_pos(t_general *G, char **map);
void	player_direction(t_general *G, char flag);
int32_t	ft_pixel(int32_t	r, int32_t g, int32_t b, int32_t a);
void	ceiling_and_floor(t_general *G);
void	texture_path(t_map *map);
int		cast_ray2(t_array *r, char **map);
void	d_collision(t_array *r, t_wall *wall);
void	cast_ray(t_general *G, char **map);
void	rotation(t_vec *vec, short sign);
void	movement(t_general *G, t_vec *vec);	
void	dirxl(t_array	*r, t_vec	*vec);
void	dirxr(t_array	*r, t_vec	*vec);
void	diryu(t_array	*r, t_vec	*vec);
void	diryd(t_array	*r, t_vec	*vec);
void	walls(t_wall *wall, short x, t_general *G, t_array *r);
void	set_texture(t_texture *t, t_wall *wall,
			mlx_texture_t *text, t_array *r);
void	texture(t_texture *t, t_wall *wall, t_general *G, t_array *r);
void	keyhooks(void *param);

#endif