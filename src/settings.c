/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmehadje <rmehadje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:43:56 by rmehadje          #+#    #+#             */
/*   Updated: 2024/04/04 15:39:24 by rmehadje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	texture_path(t_map *map)
{
	map->texture[0] = "textures/texture1.png";
	map->texture[1] = "textures/texture2.png";
	map->texture[2] = "textures/texture3.png";
	map->texture[3] = "textures/texture4.png";
}
