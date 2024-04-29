/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:26:02 by mobadiah          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:26 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 
char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*d;

	d = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (d == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		d[i] = s2[j];
		i++;
		j++;
	}
	d[i] = '\0';
	return (d);
}
