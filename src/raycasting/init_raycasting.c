/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:46 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 13:59:22 by jcario           ###   ########.fr       */
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

void	init_raycasting(t_game *game)
{
	game->rc.dir.x = -0.5;
	game->rc.dir.y = 0;
	game->rc.plane.x = 0;
	game->rc.plane.y = 0.90;
	game->img.play_animation = FALSE;
	get_starting_direction(game);
	load_textures(game);
	if (!game->textures.textures[0] || !game->textures.textures[1]
		|| !game->textures.textures[2] || !game->textures.textures[3]
		|| !game->textures.textures[4] || !game->textures.textures[5]
		|| !game->textures.ceiling || !game->textures.floor)
		end(game, 1);
	set_gui(game);
}

void	init_sword(t_game *game)
{
	game->img.sword[0] = load_image(game, "./textures/sword/1.png");
	game->img.sword[1] = load_image(game, "./textures/sword/2.png");
	game->img.sword[2] = load_image(game, "./textures/sword/3.png");
	game->img.sword[3] = load_image(game, "./textures/sword/4.png");
	game->img.sword[4] = load_image(game, "./textures/sword/5.png");
	mlx_image_to_window(game->mlx, game->img.sword[0], 0, 0);
	mlx_image_to_window(game->mlx, game->img.sword[1], 0, 0);
	mlx_image_to_window(game->mlx, game->img.sword[2], 0, 0);
	mlx_image_to_window(game->mlx, game->img.sword[3], 0, 0);
	mlx_image_to_window(game->mlx, game->img.sword[4], 0, 0);
	mlx_set_instance_depth(game->img.sword[0]->instances, 9);
	mlx_set_instance_depth(game->img.sword[1]->instances, 9);
	mlx_set_instance_depth(game->img.sword[2]->instances, 9);
	mlx_set_instance_depth(game->img.sword[3]->instances, 9);
	mlx_set_instance_depth(game->img.sword[4]->instances, 9);
	game->img.sword[1]->enabled = false;
	game->img.sword[2]->enabled = false;
	game->img.sword[3]->enabled = false;
	game->img.sword[4]->enabled = false;
}

void	init_floor_ceiling_casting(int y, t_game *game)
{
	game->rc.ray0.x = game->rc.dir.x - game->rc.plane.x;
	game->rc.ray0.y = game->rc.dir.y - game->rc.plane.y;
	game->rc.ray1.x = game->rc.dir.x + game->rc.plane.x;
	game->rc.ray1.y = game->rc.dir.y + game->rc.plane.y;
	game->rc.p = y - HEIGHT / 2;
	game->rc.pos_z = 0.5 * HEIGHT;
	game->rc.row_distance = game->rc.pos_z / game->rc.p;
	game->rc.floor_step.x = game->rc.row_distance
		* (game->rc.ray1.x - game->rc.ray0.x) / WIDTH;
	game->rc.floor_step.y = game->rc.row_distance
		* (game->rc.ray1.y - game->rc.ray0.y) / WIDTH;
	game->rc.floor.x = game->rc.pos.x + game->rc.row_distance * game->rc.ray0.x;
	game->rc.floor.y = game->rc.pos.y + game->rc.row_distance * game->rc.ray0.y;
}

static void	calculate_ray_properties(t_game *game)
{
	if (game->rc.ray.x < 0)
	{
		game->rc.step.x = -1;
		game->rc.side_dist.x = (game->rc.pos.x - game->rc.map_pos.x)
			* game->rc.delta_dist.x;
	}
	else
	{
		game->rc.step.x = 1;
		game->rc.side_dist.x = (game->rc.map_pos.x + 1.0 - game->rc.pos.x)
			* game->rc.delta_dist.x;
	}
	if (game->rc.ray.y < 0)
	{
		game->rc.step.y = -1;
		game->rc.side_dist.y = (game->rc.pos.y - game->rc.map_pos.y)
			* game->rc.delta_dist.y;
	}
	else
	{
		game->rc.step.y = 1;
		game->rc.side_dist.y = (game->rc.map_pos.y + 1.0 - game->rc.pos.y)
			* game->rc.delta_dist.y;
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
	game->rc.map_pos.x = (int)game->rc.pos.x;
	game->rc.map_pos.y = (int)game->rc.pos.y;
	if (!game->rc.ray.x)
		game->rc.delta_dist.x = 1e30;
	else
		game->rc.delta_dist.x = fabs(1 / game->rc.ray.x);
	if (!game->rc.ray.y)
		game->rc.delta_dist.y = 1e30;
	else
		game->rc.delta_dist.y = fabs(1 / game->rc.ray.y);
	game->rc.hit = 0;
	game->rc.is_door = 0;
	calculate_ray_properties(game);
}
