/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:09:29 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 13:39:58 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_textures(t_game *game)
{
	free(game->map.ceiling_texture);
	free(game->map.floor_texture);
	free(game->map.north_texture);
	free(game->map.west_texture);
	free(game->map.east_texture);
	free(game->map.south_texture);
}

void	del_mlx(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (game->textures.textures[i])
			mlx_delete_texture(game->textures.textures[i]);
	mlx_delete_image(game->mlx, game->img.hotbar);
	mlx_delete_image(game->mlx, game->img.cursor);
	if (game->textures.ceiling)
		mlx_delete_texture(game->textures.ceiling);
	if (game->textures.floor)
		mlx_delete_texture(game->textures.floor);
}

void	end(t_game *game, int error_code)
{
	int	i;

	i = -1;
	free_matrix(game->map.map);
	free_textures(game);
	if (error_code == 0)
		exit(0);
	del_mlx(game);
	if (error_code != 1)
		while (++i < 5)
			mlx_delete_image(game->mlx, game->img.sword[i]);
	mlx_terminate(game->mlx);
	exit(0);
}

/*
MAP
TEXTURES (noms)
TEXTURES (mlx_textures)
IMAGES (ceiling / floor)
IMAGES (sword)
*/