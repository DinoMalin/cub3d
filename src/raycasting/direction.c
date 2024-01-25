/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:50:27 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 16:15:29 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	rotate_left(t_game *game, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->rc.dir.x;
	old_plane_x = game->rc.plane.x;
	game->rc.dir.x = game->rc.dir.x * cos(rotation_angle) - game->rc.dir.y
		* sin(rotation_angle);
	game->rc.dir.y = old_dir_x * sin(rotation_angle) + game->rc.dir.y
		* cos(rotation_angle);
	game->rc.plane.x = game->rc.plane.x * cos(rotation_angle) - game->rc.plane.y
		* sin(rotation_angle);
	game->rc.plane.y = old_plane_x * sin(rotation_angle) + game->rc.plane.y
		* cos(rotation_angle);
}

void	rotate_right(t_game *game, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->rc.dir.x;
	old_plane_x = game->rc.plane.x;
	game->rc.dir.x = game->rc.dir.x * cos(-rotation_angle) - game->rc.dir.y
		* sin(-rotation_angle);
	game->rc.dir.y = old_dir_x * sin(-rotation_angle) + game->rc.dir.y
		* cos(-rotation_angle);
	game->rc.plane.x = game->rc.plane.x * cos(-rotation_angle)
		- game->rc.plane.y * sin(-rotation_angle);
	game->rc.plane.y = old_plane_x * sin(-rotation_angle) + game->rc.plane.y
		* cos(-rotation_angle);
}

void	get_starting_direction(t_game *game)
{
	if (game->map.starting_direction == 'N')
		return ;
	else if (game->map.starting_direction == 'S')
		rotate_right(game, PI);
	else if (game->map.starting_direction == 'E')
		rotate_right(game, PI / 2);
	else if (game->map.starting_direction == 'W')
		rotate_left(game, PI / 2);
}

double	get_rotation_angle(t_game *game)
{
	double	radians;
	double	degrees;

	radians = atan2(game->rc.dir.y, game->rc.dir.x);
	degrees = radians * (180.0 / PI);
	degrees = fmod((degrees + 360.0), 360.0);
	return (degrees);
}
