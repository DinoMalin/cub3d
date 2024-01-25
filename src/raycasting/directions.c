/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:45:22 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 14:38:46 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	up(t_game *game)
{
	if (!ft_strchr("1D", game->map.map[(int)(game->rc.pos.x + game->rc.dir.x
				* MOVE_SPEED)][(int)game->rc.pos.y]))
		game->rc.pos.x += game->rc.dir.x * MOVE_SPEED;
	if (!ft_strchr("1D", game->map.map[(int)game->rc.pos.x]
			[(int)(game->rc.pos.y + game->rc.dir.y * MOVE_SPEED)]))
		game->rc.pos.y += game->rc.dir.y * MOVE_SPEED;
}

void	down(t_game *game)
{
	if (!ft_strchr("1D", game->map.map[(int)(game->rc.pos.x - game->rc.dir.x
				* MOVE_SPEED)][(int)game->rc.pos.y]))
		game->rc.pos.x -= game->rc.dir.x * MOVE_SPEED;
	if (!ft_strchr("1D", game->map.map[(int)game->rc.pos.x]
			[(int)(game->rc.pos.y - game->rc.dir.y * MOVE_SPEED)]))
		game->rc.pos.y -= game->rc.dir.y * MOVE_SPEED;
}

void	right(t_game *game)
{
	if (!ft_strchr("1D", game->map.map[(int)(game->rc.pos.x + game->rc.plane.x
				* MOVE_SPEED / 2)][(int)game->rc.pos.y]))
		game->rc.pos.x += game->rc.plane.x * MOVE_SPEED / 2;
	if (!ft_strchr("1D", game->map.map[(int)game->rc.pos.x]
			[(int)(game->rc.pos.y + game->rc.plane.y * MOVE_SPEED / 2)]))
		game->rc.pos.y += game->rc.plane.y * MOVE_SPEED / 2;
}

void	left(t_game *game)
{
	if (!ft_strchr("1D", game->map.map[(int)(game->rc.pos.x - game->rc.plane.x
				* MOVE_SPEED / 2)][(int)game->rc.pos.y]))
		game->rc.pos.x -= game->rc.plane.x * MOVE_SPEED / 2;
	if (!ft_strchr("1D", game->map.map[(int)game->rc.pos.x]
			[(int)(game->rc.pos.y - game->rc.plane.y * MOVE_SPEED / 2)]))
		game->rc.pos.y -= game->rc.plane.y * MOVE_SPEED / 2;
}
