/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:46 by jcario            #+#    #+#             */
/*   Updated: 2024/01/19 17:05:06 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_raycasting(t_game *game)
{
	game->rc.dir.x = -0.5;
	game->rc.dir.y = 0;
	game->rc.plane.x = 0;
	game->rc.plane.y = 0.90;
	get_starting_direction(game);
	game->textures.textures[0] = mlx_load_png(game->map.north_texture);
	game->textures.textures[1] = mlx_load_png(game->map.west_texture);
	game->textures.floor = mlx_load_png(game->map.floor_texture);
	game->textures.ceiling = mlx_load_png(game->map.ceiling_texture);
	if (!game->textures.textures[0] || !game->textures.textures[1] || !game->textures.ceiling || !game->map.floor_texture || !game->map.west_texture)
		end(game);
	game->textures.sword = mlx_load_png("./textures/sword.png");
	game->textures.sword_img = mlx_texture_to_image(game->mlx, game->textures.sword);
	game->textures.hotbar = mlx_load_png("./textures/hotbar.png");
	game->textures.hotbar_img = mlx_texture_to_image(game->mlx, game->textures.hotbar);
	game->textures.cursor = mlx_load_png("./textures/cross.png");
	game->textures.cursor_img = mlx_texture_to_image(game->mlx, game->textures.cursor);
	mlx_image_to_window(game->mlx, game->textures.sword_img, WIDTH - game->textures.sword->width / 1.5, HEIGHT - game->textures.sword->height);
	mlx_image_to_window(game->mlx, game->textures.hotbar_img, WIDTH / 2 - game->textures.hotbar->width / 2, HEIGHT - game->textures.hotbar->height);
	mlx_image_to_window(game->mlx, game->textures.cursor_img, WIDTH / 2 - game->textures.cursor->width / 2, HEIGHT / 2 - game->textures.cursor->height / 2);
	mlx_set_instance_depth(game->textures.sword_img->instances, 10);
	mlx_set_instance_depth(game->textures.hotbar_img->instances, 10);
	mlx_set_instance_depth(game->textures.cursor_img->instances, 11);
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
	game->rc.camera.x = 2 * x / (double)WIDTH - 1;
	game->rc.ray.x = game->rc.dir.x + game->rc.plane.x * game->rc.camera.x;
	game->rc.ray.y = game->rc.dir.y + game->rc.plane.y * game->rc.camera.x;
	game->rc.mapPos.x = (int)game->rc.pos.x;
	game->rc.mapPos.y = (int)game->rc.pos.y;
	game->rc.deltaDist.x = (game->rc.ray.x == 0) ? 1e30 : fabs(1 / game->rc.ray.x);
	game->rc.deltaDist.y = (game->rc.ray.y == 0) ? 1e30 : fabs(1 / game->rc.ray.y);
	game->rc.hit = 0;
	calculate_ray_properties(game);
}
