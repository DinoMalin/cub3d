/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:45:22 by jcario            #+#    #+#             */
/*   Updated: 2024/01/16 13:43:49 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	left(t_game *game, double rotation_angle)
{
	double	oldDirX = game->rc.dir.x;
	double	oldPlaneX = game->rc.plane.x;

	game->rc.dir.x = game->rc.dir.x * cos(rotation_angle) - game->rc.dir.y * sin(rotation_angle);
	game->rc.dir.y = oldDirX * sin(rotation_angle) + game->rc.dir.y * cos(rotation_angle);
	game->rc.plane.x = game->rc.plane.x * cos(rotation_angle) - game->rc.plane.y * sin(rotation_angle);
	game->rc.plane.y = oldPlaneX * sin(rotation_angle) + game->rc.plane.y * cos(rotation_angle);
}

void	right(t_game *game, double rotation_angle)
{
	double	oldDirX = game->rc.dir.x;
	double	oldPlaneX = game->rc.plane.x;

	game->rc.dir.x = game->rc.dir.x * cos(-rotation_angle) - game->rc.dir.y * sin(-rotation_angle);
	game->rc.dir.y = oldDirX * sin(-rotation_angle) + game->rc.dir.y * cos(-rotation_angle);
	game->rc.plane.x = game->rc.plane.x * cos(-rotation_angle) - game->rc.plane.y * sin(-rotation_angle);
	game->rc.plane.y = oldPlaneX * sin(-rotation_angle) + game->rc.plane.y * cos(-rotation_angle);
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

void	get_starting_direction(t_game *game)
{
	if (game->map.starting_direction == 'N')
		return ;
	else if (game->map.starting_direction == 'S')
		right(game, PI);
	else if (game->map.starting_direction == 'E')
		right(game, PI / 2);
	else if (game->map.starting_direction == 'W')
		left(game, PI / 2);
}
