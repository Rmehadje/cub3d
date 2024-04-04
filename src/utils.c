/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:36:34 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/04 15:39:26 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	open_file(char *file, int *fd, char **content)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	*content = malloc(5000000);
	if (!*content)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (read(*fd, *content, 5000000) == -1)
	{
		perror("Error reading file");
		free(*content);
		close(*fd);
		exit(EXIT_FAILURE);
	}
	close(*fd);
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
	free(str);
	str = NULL;
}