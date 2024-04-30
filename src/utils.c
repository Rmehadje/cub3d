/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:36:34 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 21:00:40 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *msg, t_general *g, t_map *m, int flag)
{
	int	i;

	if (flag)
	{
		i = -1;
		while (++i < 4)
		{
			if (g && g->walls[i])
				mlx_delete_texture(g->walls[i]);
			if (m->texture[i])
				free(m->texture[i]);
		}
		if (g && g->img)
			mlx_delete_image(g->mlx, g->img);
		if (g && g->mlx)
			mlx_terminate(g->mlx);
		if (m->map)
			ft_free2(m->map);
	}
	if (msg)
		printf("%s\n", msg);
	exit(flag);
}

void	ft_free2(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_free(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	str = NULL;
}

char	*ft_strdup2(const char *s1)
{
	int		i;
	char	*result;
	int		size;

	size = 0;
	while (s1[size] && s1[size] != '\n')
		size++;
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
