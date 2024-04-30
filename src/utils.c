/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:36:34 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/30 14:57:58 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *str)
{
	while (*str)
		write(2, str++, 1);
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
