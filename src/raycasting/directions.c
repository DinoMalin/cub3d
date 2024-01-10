/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:45:22 by jcario            #+#    #+#             */
/*   Updated: 2024/01/10 16:24:18 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	left(t_game *game)
{
	double	oldDirX = game->rc.dir.x;
	double	oldPlaneX = game->rc.plane.x;

	game->rc.dir.x = game->rc.dir.x * cos(ROTATION_SPEED) - game->rc.dir.y * sin(ROTATION_SPEED);
	game->rc.dir.y = oldDirX * sin(ROTATION_SPEED) + game->rc.dir.y * cos(ROTATION_SPEED);
	game->rc.plane.x = game->rc.plane.x * cos(ROTATION_SPEED) - game->rc.plane.y * sin(ROTATION_SPEED);
	game->rc.plane.y = oldPlaneX * sin(ROTATION_SPEED) + game->rc.plane.y * cos(ROTATION_SPEED);
}

void	right(t_game *game)
{
	double	oldDirX = game->rc.dir.x;
	double	oldPlaneX = game->rc.plane.x;

	game->rc.dir.x = game->rc.dir.x * cos(-ROTATION_SPEED) - game->rc.dir.y * sin(-ROTATION_SPEED);
	game->rc.dir.y = oldDirX * sin(-ROTATION_SPEED) + game->rc.dir.y * cos(-ROTATION_SPEED);
	game->rc.plane.x = game->rc.plane.x * cos(-ROTATION_SPEED) - game->rc.plane.y * sin(-ROTATION_SPEED);
	game->rc.plane.y = oldPlaneX * sin(-ROTATION_SPEED) + game->rc.plane.y * cos(-ROTATION_SPEED);
}

void	up(t_game *game)
{
	if(game->map.map[(int)(game->rc.pos.x + game->rc.dir.x * MOVE_SPEED)][(int)game->rc.pos.y] != '1')
		game->rc.pos.x += game->rc.dir.x * MOVE_SPEED;
	if(game->map.map[(int)game->rc.pos.x][(int)(game->rc.pos.y + game->rc.dir.y * MOVE_SPEED)] != '1')
		game->rc.pos.y += game->rc.dir.y * MOVE_SPEED;
}

void	down(t_game *game)
{
	if(game->map.map[(int)(game->rc.pos.x - game->rc.dir.x * MOVE_SPEED)][(int)game->rc.pos.y] != '1')
		game->rc.pos.x -= game->rc.dir.x * MOVE_SPEED;
	if(game->map.map[(int)game->rc.pos.x][(int)(game->rc.pos.y - game->rc.dir.y * MOVE_SPEED)] != '1')
		game->rc.pos.y -= game->rc.dir.y * MOVE_SPEED;
}
