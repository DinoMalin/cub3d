/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:10:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/16 17:13:08 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	floor_ceiling_casting(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		init_floor_ceiling_casting(y, game);
		while (++x < WIDTH)
		{
			game->rc.cell.x = (int)(game->rc.floor.x);
			game->rc.cell.y = (int)(game->rc.floor.y);
			game->rc.texture.x = (int)(game->textures.floor->width * (game->rc.floor.x - game->rc.cell.x)) & (game->textures.floor->width - 1);
			game->rc.texture.y = (int)(game->textures.floor->height * (game->rc.floor.y - game->rc.cell.y)) & (game->textures.floor->height - 1);
			game->rc.floor.x += game->rc.floorStep.x;
			game->rc.floor.y += game->rc.floorStep.y;
			game->rc.color = &game->textures.floor->pixels[(game->textures.floor->width * game->rc.texture.y + game->rc.texture.x) * 4];
			game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0], game->rc.color[1], game->rc.color[2], game->rc.color[3]);
			game->rc.color = &game->textures.ceiling->pixels[(game->textures.floor->width * game->rc.texture.y + game->rc.texture.x) * 4];
			game->rc.screen_buffer[x][HEIGHT - y - 1] = get_rgba(game->rc.color[0], game->rc.color[1], game->rc.color[2], game->rc.color[3]);
		}
	}
}

void	walls_casting(t_game *game)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		init_walls_casting(x, game);
		while (!game->rc.hit)
		{
			game->rc.side = !(game->rc.sideDist.x < game->rc.sideDist.y);
			if (!game->rc.side)
			{
				game->rc.sideDist.x += game->rc.deltaDist.x;
				game->rc.mapPos.x += game->rc.step.x;
			}
			else
			{
				game->rc.sideDist.y += game->rc.deltaDist.y;
				game->rc.mapPos.y += game->rc.step.y;
			}
			if (game->map.map[game->rc.mapPos.x][game->rc.mapPos.y] == '1')
				game->rc.hit = 1;
		}
		calculate_texture(game);
		draw_texture(x, game);
	}
}

void	process_raycasting(t_game *game)
{
	static int count = 0;
	static mlx_image_t *current_img;

	if (count > 0)
		mlx_delete_image(game->mlx, current_img);
	current_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	floor_ceiling_casting(game);
	walls_casting(game);
	draw_buffer(game, current_img);
	clear_buffer(game);
	mlx_image_to_window(game->mlx, current_img, 0, 0);
	mlx_set_instance_depth(current_img->instances, 1);
	count++;
}
