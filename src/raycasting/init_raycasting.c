/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:46 by jcario            #+#    #+#             */
/*   Updated: 2024/01/15 13:09:31 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_raycasting(t_game *game)
{
	game->rc.dir.x = -0.5;
	game->rc.dir.y = 0;
	game->rc.plane.x = 0;
	game->rc.plane.y = 0.90;
	game->textures.north_wall = mlx_load_png("./textures/cobblestone.png");
	game->textures.floor = mlx_load_png("./textures/plank.png");
	game->textures.ceiling = mlx_load_png("./textures/plank.png");
	if (!game->textures.north_wall)
		ft_printf("error");
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
