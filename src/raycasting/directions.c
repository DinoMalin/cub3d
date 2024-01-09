/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:45:22 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 21:51:24 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	left(t_game *game)
{
	double	oldDirX = game->rc.dirX;
	double	oldPlaneX = game->rc.planeX;

	game->rc.dirX = game->rc.dirX * cos(ROTATION_SPEED) - game->rc.dirY * sin(ROTATION_SPEED);
	game->rc.dirY = oldDirX * sin(ROTATION_SPEED) + game->rc.dirY * cos(ROTATION_SPEED);
	game->rc.planeX = game->rc.planeX * cos(ROTATION_SPEED) - game->rc.planeY * sin(ROTATION_SPEED);
	game->rc.planeY = oldPlaneX * sin(ROTATION_SPEED) + game->rc.planeY * cos(ROTATION_SPEED);
}

void	right(t_game *game)
{
	double	oldDirX = game->rc.dirX;
	double	oldPlaneX = game->rc.planeX;

	game->rc.dirX = game->rc.dirX * cos(-ROTATION_SPEED) - game->rc.dirY * sin(-ROTATION_SPEED);
	game->rc.dirY = oldDirX * sin(-ROTATION_SPEED) + game->rc.dirY * cos(-ROTATION_SPEED);
	game->rc.planeX = game->rc.planeX * cos(-ROTATION_SPEED) - game->rc.planeY * sin(-ROTATION_SPEED);
	game->rc.planeY = oldPlaneX * sin(-ROTATION_SPEED) + game->rc.planeY * cos(-ROTATION_SPEED);
}

void	up(t_game *game)
{
	if(game->map.map[(int)(game->rc.posX + game->rc.dirX * MOVE_SPEED)][(int)game->rc.posY] != '1')
		game->rc.posX += game->rc.dirX * MOVE_SPEED;
	if(game->map.map[(int)game->rc.posX][(int)(game->rc.posY + game->rc.dirY * MOVE_SPEED)] != '1')
		game->rc.posY += game->rc.dirY * MOVE_SPEED;
}

void	down(t_game *game)
{
	if(game->map.map[(int)(game->rc.posX - game->rc.dirX * MOVE_SPEED)][(int)game->rc.posY] != '1')
		game->rc.posX -= game->rc.dirX * MOVE_SPEED;
	if(game->map.map[(int)game->rc.posX][(int)(game->rc.posY - game->rc.dirY * MOVE_SPEED)] != '1')
		game->rc.posY -= game->rc.dirY * MOVE_SPEED;
}
