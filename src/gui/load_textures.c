/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:51:14 by jcario            #+#    #+#             */
/*   Updated: 2024/01/26 14:56:00 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	load_textures(t_game *game)
{
	game->textures.textures[0] = mlx_load_png(game->map.north_texture);
	game->textures.textures[1] = mlx_load_png(game->map.south_texture);
	game->textures.textures[2] = mlx_load_png(game->map.west_texture);
	game->textures.textures[3] = mlx_load_png(game->map.east_texture);
	game->textures.textures[4] = mlx_load_png("./textures/diamond.png");
	game->textures.textures[5] = mlx_load_png("./textures/diamond_2.png");
	game->textures.floor = mlx_load_png(game->map.floor_texture);
	game->textures.ceiling = mlx_load_png(game->map.ceiling_texture);
	game->img.hotbar = load_image(game, "./textures/hotbar.png");
	game->img.cursor = load_image(game, "./textures/cross.png");
}

void	set_gui(t_game *game)
{
	mlx_image_to_window(game->mlx, game->img.hotbar,
		WIDTH / 2 - game->img.hotbar->width / 2,
		HEIGHT - game->img.hotbar->height);
	mlx_image_to_window(game->mlx,
		game->img.cursor, WIDTH / 2 - game->img.cursor->width / 2,
		HEIGHT / 2 - game->img.cursor->height / 2);
	mlx_set_instance_depth(game->img.hotbar->instances, 10);
	mlx_set_instance_depth(game->img.cursor->instances, 11);
	game->map.cast_minimap = FALSE;
	game->map.ratio = 10;
	game->map.minimap = mlx_new_image(game->mlx,
			game->map.width * game->map.ratio,
			game->map.height * game->map.ratio);
	game->map.minimap->enabled = false;
	mlx_image_to_window(game->mlx, game->map.minimap,
		WIDTH / 2 - game->map.minimap->width / 2,
		HEIGHT / 2 - game->map.minimap->height / 2);
}

void	init_sword(t_game *game)
{
	int	i;

	game->img.sword[0] = load_image(game, "./textures/sword/1.png");
	game->img.sword[1] = load_image(game, "./textures/sword/2.png");
	game->img.sword[2] = load_image(game, "./textures/sword/3.png");
	game->img.sword[3] = load_image(game, "./textures/sword/4.png");
	game->img.sword[4] = load_image(game, "./textures/sword/5.png");
	i = -1;
	while (++i < 5)
		mlx_image_to_window(game->mlx, game->img.sword[i], 0, 0);
	i = -1;
	while (++i < 5)
		mlx_set_instance_depth(game->img.sword[i]->instances, 9);
	i = 0;
	while (++i < 5)
		game->img.sword[i]->enabled = false;
}
