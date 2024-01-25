/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:10:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 15:56:18 by jcario           ###   ########.fr       */
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
			game->rc.texture.x = (int)(game->textures.floor->width
					* (game->rc.floor.x - game->rc.cell.x))
				& (game->textures.floor->width - 1);
			game->rc.texture.y = (int)(game->textures.floor->height
					* (game->rc.floor.y - game->rc.cell.y))
				& (game->textures.floor->height - 1);
			game->rc.floor.x += game->rc.floor_step.x;
			game->rc.floor.y += game->rc.floor_step.y;
			get_floor_texture(game, x, y);
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
			get_adequate_texture(game);
			if (!game->rc.side)
			{
				game->rc.side_dist.x += game->rc.delta_dist.x;
				game->rc.map_pos.x += game->rc.step.x;
			}
			else
			{
				game->rc.side_dist.y += game->rc.delta_dist.y;
				game->rc.map_pos.y += game->rc.step.y;
			}
			game->rc.hit = ft_strchr("1D", game->map.map[game->rc.map_pos.x]
				[game->rc.map_pos.y]) != NULL;
			get_door_texture(game);
		}
		calculate_texture(game, x);
	}
}

void	process_raycasting(t_game *game)
{
	static int			count = 0;
	static mlx_image_t	*current_img;

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
