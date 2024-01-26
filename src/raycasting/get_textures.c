/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:55:28 by jcario            #+#    #+#             */
/*   Updated: 2024/01/26 14:56:11 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_floor_texture(t_game *game, int x, int y)
{
	game->rc.color = &game->textures.floor->pixels[(game->textures.floor->width
			* game->rc.texture.y + game->rc.texture.x) * 4];
	game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0],
			game->rc.color[1], game->rc.color[2], game->rc.color[3]);
	game->rc.color = &game->textures.ceiling->pixels
	[(game->textures.floor->width * game->rc.texture.y
			+ game->rc.texture.x) * 4];
	game->rc.screen_buffer[x][HEIGHT - y - 1] = get_rgba(game->rc.color[0],
			game->rc.color[1], game->rc.color[2], game->rc.color[3]);
}

void	get_adequate_texture(t_game *game)
{
	game->rc.side = !(game->rc.side_dist.x < game->rc.side_dist.y);
	if (game->rc.side == 0 && game->rc.ray.x >= 0)
		game->rc.tex_num = 0;
	else if (game->rc.side == 0 && game->rc.ray.x < 0)
		game->rc.tex_num = 1;
	else if (game->rc.side == 1 && game->rc.ray.y >= 0)
		game->rc.tex_num = 2;
	else if (game->rc.side == 1 && game->rc.ray.y < 0)
		game->rc.tex_num = 3;
}

void	get_door_texture(t_game *game)
{
	if (game->map.map[game->rc.map_pos.x][game->rc.map_pos.y] == 'D'
		&& game->rc.side)
		game->rc.tex_num = 4;
	if (game->map.map[game->rc.map_pos.x][game->rc.map_pos.y] == 'D'
		&& !game->rc.side)
		game->rc.tex_num = 5;
}

void	get_tex_x(t_game *game)
{
	if (!game->rc.side && game->rc.ray.x > 0)
		game->rc.texx = game->textures.textures[game->rc.tex_num]->width
			- game->rc.texx - 1;
	if (game->rc.side && game->rc.ray.y < 0)
		game->rc.texx = game->textures.textures[game->rc.tex_num]->width
			- game->rc.texx - 1;
}
