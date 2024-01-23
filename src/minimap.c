/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:06 by jcario            #+#    #+#             */
/*   Updated: 2024/01/23 17:51:34 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	cast_minimap(t_game *game)
{
	mlx_image_t	*img;
	int	ratio;
	int	i;
	int	j;

	i = -1;
	ratio = 20;
	img = mlx_new_image(game->mlx, game->map.width * ratio, game->map.height * ratio);
	while (game->map.map[++i / ratio])
	{
		j = -1;
		while (game->map.map[i / ratio][++j / ratio])
		{
			if (game->map.map[i / ratio][j / ratio] == '1')
				mlx_put_pixel(img, j, i, 0xcca37cff);
			else if (ft_strchr("0NWES", game->map.map[i / ratio][j / ratio]))
				mlx_put_pixel(img, j, i, 0xb6c4cfff);
			else if (game->map.map[i / ratio][j / ratio] == 'D')
				mlx_put_pixel(img, j, i, 0x0094F0ff);
		}
	}
	mlx_image_to_window(game->mlx, img, 0, 0);
}