/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:06 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 15:07:54 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_minimap(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i / game->map.ratio])
	{
		j = -1;
		while (game->map.map[i / game->map.ratio][++j / game->map.ratio])
		{
			if (game->map.map[i / game->map.ratio][j / game->map.ratio] == '1')
				mlx_put_pixel(game->map.minimap, j, i, 0x776B5DC0);
			else if (ft_strchr("0NWES", game->map.map[i / game->map.ratio]
					[j / game->map.ratio]))
				mlx_put_pixel(game->map.minimap, j, i, 0xEBE3D5C0);
			else if (game->map.map[i / game->map.ratio]
				[j / game->map.ratio] == 'D')
				mlx_put_pixel(game->map.minimap, j, i, 0x8c7d6cC0);
			else
				mlx_put_pixel(game->map.minimap, j, i, 0x8c7d6c00);
			if ((int)game->rc.pos.x == i / game->map.ratio
				&& (int)game->rc.pos.y == j / game->map.ratio)
				mlx_put_pixel(game->map.minimap, j, i, 0x6499E9C0);
		}
	}
}

void	minimap_handler(t_game *game)
{
	if (game->map.cast_minimap)
	{
		game->map.minimap->enabled = true;
		create_minimap(game);
	}
	else
		game->map.minimap->enabled = false;
}
