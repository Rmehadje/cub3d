/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:34:07 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/29 12:40:05 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include	<unistd.h>
# include	<fcntl.h>
# include	<string.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	"libft.h"


char				*get_next_line(int fd);
char				*ft_get_line(int fd, char *stat, char *tmp);

#endif