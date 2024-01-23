/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:46 by jcario            #+#    #+#             */
/*   Updated: 2024/01/23 18:09:57 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_raycasting(t_game *game)
{
	game->rc.dir.x = -0.5;
	game->rc.dir.y = 0;
	game->rc.plane.x = 0;
	game->rc.plane.y = 0.90;
	game->textures.play_animation = FALSE;
	get_starting_direction(game);
	game->textures.textures[0] = mlx_load_png(game->map.north_texture);
	game->textures.textures[1] = mlx_load_png(game->map.south_texture);
	game->textures.textures[2] = mlx_load_png(game->map.west_texture);
	game->textures.textures[3] = mlx_load_png(game->map.east_texture);
	game->textures.textures[4] = mlx_load_png("./textures/diamond.png");
	game->textures.textures[5] = mlx_load_png("./textures/diamond_2.png");
	game->textures.floor = mlx_load_png(game->map.floor_texture);
	game->textures.ceiling = mlx_load_png(game->map.ceiling_texture);
	if (!game->textures.textures[0] || !game->textures.textures[1] || !game->textures.textures[2] || !game->textures.textures[3] || !game->textures.ceiling || !game->map.floor_texture || !game->map.west_texture)
		end(game);
	game->textures.hotbar = load_image(game, "./textures/hotbar.png");
	game->textures.cursor = load_image(game, "./textures/cross.png");
	mlx_image_to_window(game->mlx, game->textures.hotbar, WIDTH / 2 - game->textures.hotbar->width / 2, HEIGHT - game->textures.hotbar->height);
	mlx_image_to_window(game->mlx, game->textures.cursor, WIDTH / 2 - game->textures.cursor->width / 2, HEIGHT / 2 - game->textures.cursor->height / 2);
	mlx_set_instance_depth(game->textures.hotbar->instances, 10);
	mlx_set_instance_depth(game->textures.cursor->instances, 11);
}

void	init_sword(t_game *game)
{
	game->textures.sword[0] = load_image(game, "./textures/sword/1.png");
	game->textures.sword[1] = load_image(game, "./textures/sword/2.png");
	game->textures.sword[2] = load_image(game, "./textures/sword/3.png");
	game->textures.sword[3] = load_image(game, "./textures/sword/4.png");
	game->textures.sword[4] = load_image(game, "./textures/sword/5.png");
	mlx_image_to_window(game->mlx, game->textures.sword[0], 0, 0);
	mlx_image_to_window(game->mlx, game->textures.sword[1], 0, 0);
	mlx_image_to_window(game->mlx, game->textures.sword[2], 0, 0);
	mlx_image_to_window(game->mlx, game->textures.sword[3], 0, 0);
	mlx_image_to_window(game->mlx, game->textures.sword[4], 0, 0);
	mlx_set_instance_depth(game->textures.sword[0]->instances, 9);
	mlx_set_instance_depth(game->textures.sword[1]->instances, 9);
	mlx_set_instance_depth(game->textures.sword[2]->instances, 9);
	mlx_set_instance_depth(game->textures.sword[3]->instances, 9);
	mlx_set_instance_depth(game->textures.sword[4]->instances, 9);
	game->textures.sword[1]->enabled = false;
	game->textures.sword[2]->enabled = false;
	game->textures.sword[3]->enabled = false;
	game->textures.sword[4]->enabled = false;
}

void	init_floor_ceiling_casting(int y, t_game *game)
{
	game->rc.ray0.x = game->rc.dir.x - game->rc.plane.x;
	game->rc.ray0.y = game->rc.dir.y - game->rc.plane.y;
	game->rc.ray1.x = game->rc.dir.x + game->rc.plane.x;
	game->rc.ray1.y = game->rc.dir.y + game->rc.plane.y;
	game->rc.p = y - HEIGHT / 2;
	game->rc.posZ = 0.5 * HEIGHT;
	game->rc.rowDistance = game->rc.posZ / game->rc.p;
	game->rc.floorStep.x = game->rc.rowDistance * (game->rc.ray1.x - game->rc.ray0.x) / WIDTH;
	game->rc.floorStep.y = game->rc.rowDistance * (game->rc.ray1.y - game->rc.ray0.y) / WIDTH;
	game->rc.floor.x = game->rc.pos.x + game->rc.rowDistance * game->rc.ray0.x;
	game->rc.floor.y = game->rc.pos.y + game->rc.rowDistance * game->rc.ray0.y;
}

static void	calculate_ray_properties(t_game *game)
{
	if (game->rc.ray.x < 0)
	{
		game->rc.step.x = -1;
		game->rc.sideDist.x = (game->rc.pos.x - game->rc.mapPos.x) * game->rc.deltaDist.x;
	}
	else
	{
		game->rc.step.x = 1;
		game->rc.sideDist.x = (game->rc.mapPos.x + 1.0 - game->rc.pos.x) * game->rc.deltaDist.x;
	}
	if (game->rc.ray.y < 0)
	{
		game->rc.step.y = -1;
		game->rc.sideDist.y = (game->rc.pos.y - game->rc.mapPos.y) * game->rc.deltaDist.y;
	}
	else
	{
		game->rc.step.y = 1;
		game->rc.sideDist.y = (game->rc.mapPos.y + 1.0 - game->rc.pos.y) * game->rc.deltaDist.y;
	}
}

void	init_walls_casting(int x, t_game *game)
{
	if (game->drunk)
		game->rc.camera.x = 2 * x / (double)WIDTH - 1.1;
	else
		game->rc.camera.x = 2 * x / (double)WIDTH - 1;
	game->rc.ray.x = game->rc.dir.x + game->rc.plane.x * game->rc.camera.x;
	game->rc.ray.y = game->rc.dir.y + game->rc.plane.y * game->rc.camera.x;
	game->rc.mapPos.x = (int)game->rc.pos.x;
	game->rc.mapPos.y = (int)game->rc.pos.y;
	game->rc.deltaDist.x = (game->rc.ray.x == 0) ? 1e30 : fabs(1 / game->rc.ray.x);
	game->rc.deltaDist.y = (game->rc.ray.y == 0) ? 1e30 : fabs(1 / game->rc.ray.y);
	game->rc.hit = 0;
	game->rc.is_door = 0;
	calculate_ray_properties(game);
}
