/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:21:06 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:42 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(int fd, char *stat, char *tmp)
{
	int	bytes;

	if (stat == NULL)
		stat = ft_strdup("");
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			free(stat);
			return (NULL);
		}
		tmp[bytes] = '\0';
		stat = ft_strjoin(stat, tmp);
		if (ft_strchr(stat, '\n'))
			break ;
	}
	free(tmp);
	return (stat);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*stat;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc(BUFFER_SIZE + 1);
	if (tmp == 0)
		return (0);
	tmp = ft_get_line(fd, stat, tmp);
	if (!tmp)
	{
		stat = NULL;
		return (NULL);
	}
	if (tmp && tmp[0] == '\0')
		return (free(tmp), NULL);
	line = ft_substr(tmp, 0, ft_strlen(tmp)
			- ft_strlen(ft_strchr(tmp, '\n')) + 1);
	stat = ft_substr(tmp, ft_strlen(tmp)
			- ft_strlen(ft_strchr(tmp, '\n')) + 1, ft_strlen(tmp));
	free (tmp);
	return (line);
}
