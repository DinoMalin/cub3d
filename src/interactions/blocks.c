/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:00:20 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 16:02:16 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_direction(t_game *game)
{
	int	angle;

	angle = get_rotation_angle(game);
	if (angle <= 45 || angle > 315)
		return (0);
	else if (angle >= 135 && angle < 225)
		return (1);
	else if (angle > 45 && angle < 135)
		return (2);
	return (3);
}

void	destroy_block(t_game *game)
{
	game->img.play_animation = TRUE;
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == 'D'
		&& get_direction(game) == 2)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = '0';
	else if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x]
		[(int)game->rc.pos.y - 1] == 'D' && get_direction(game) == 3)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = '0';
	else if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map
		[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == 'D'
		&& get_direction(game) == 0)
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = '0';
	else if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1]
		[(int)game->rc.pos.y] == 'D' && get_direction(game) == 1)
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = '0';
}

void	place_block(t_game *game)
{
	if (ft_strchr("0NSEW", game->map.map[(int)game->rc.pos.x]
			[(int)game->rc.pos.y + 1])
		&& get_direction(game) == 2)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = 'D';
	else if ((int)game->rc.pos.y - 1 != 0
		&& ft_strchr("0NSEW", game->map.map[(int)game->rc.pos.x]
			[(int)game->rc.pos.y - 1]) && get_direction(game) == 3)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = 'D';
	else if (game->map.map[(int)game->rc.pos.x + 1]
		&& ft_strchr("0NSEW", game->map.map[(int)game->rc.pos.x + 1]
			[(int)game->rc.pos.y]) && get_direction(game) == 0)
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = 'D';
	else if ((int)game->rc.pos.x != 0
		&& ft_strchr("0NSEW", game->map.map[(int)game->rc.pos.x - 1]
			[(int)game->rc.pos.y]) && get_direction(game) == 1)
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = 'D';
}
