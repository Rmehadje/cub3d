/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:02:06 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/29 12:38:47 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = (char *)s;
	while (tmp[i])
	{
		if ((unsigned char)tmp[i] == (unsigned char)c)
			return (tmp + i);
		i++;
	}
	return (0);
}
