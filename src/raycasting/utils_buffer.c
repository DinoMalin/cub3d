/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:31:10 by jcario            #+#    #+#             */
/*   Updated: 2024/01/16 17:55:58 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_buffer(t_game *game, mlx_image_t *image)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(image, x, y, game->rc.screen_buffer[x][y]);
			x++;
		}
		y++;
	}
}

void	clear_buffer(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
			game->rc.screen_buffer[i][j++] = 0;
		i++;
	}
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	calculate_texture(t_game *game)
{
	if (!game->rc.side)
		game->rc.perpWallDist = (game->rc.sideDist.x - game->rc.deltaDist.x);
	else
		game->rc.perpWallDist = (game->rc.sideDist.y - game->rc.deltaDist.y);

	game->rc.lineHeight = (int)(HEIGHT / game->rc.perpWallDist);
	game->rc.drawStart = -game->rc.lineHeight / 2 + HEIGHT / 2;
	if(game->rc.drawStart < 0)
		game->rc.drawStart = 0;
	game->rc.drawEnd = game->rc.drawStart + game->rc.lineHeight;
	if (game->rc.drawEnd >= HEIGHT)
		game->rc.drawEnd = HEIGHT - 1;
	if (!game->rc.side)
		game->rc.wallX = game->rc.pos.y + game->rc.perpWallDist * game->rc.ray.y;
	else
		game->rc.wallX = game->rc.pos.x + game->rc.perpWallDist * game->rc.ray.x;
	game->rc.wallX -= floor(game->rc.wallX);
	game->rc.texX = (int)(game->rc.wallX * (double)game->textures.north_wall->width);
	if (!game->rc.side && game->rc.ray.x > 0)
		game->rc.texX = game->textures.north_wall->width - game->rc.texX - 1;
	if (game->rc.side  && game->rc.ray.y < 0)
		game->rc.texX = game->textures.north_wall->width - game->rc.texX - 1;
	game->rc.step_texture = 1.0 * game->textures.north_wall->height / game->rc.lineHeight;
	game->rc.texPos = (game->rc.drawStart - HEIGHT / 2 + game->rc.lineHeight / 2) * game->rc.step_texture;
}

void	draw_texture(int x, t_game *game)
{
	int	y;

	y = game->rc.drawStart - 1;
	while (++y < game->rc.drawEnd)
	{
		int texY = (int)game->rc.texPos & (game->textures.north_wall->height - 1);
		game->rc.texPos += game->rc.step_texture;
		game->rc.color = &game->textures.north_wall->pixels[(game->textures.north_wall->height * texY + game->rc.texX) * 4];
		if (game->rc.side)
			game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0] / 2, game->rc.color[1] / 2, game->rc.color[2] / 2, game->rc.color[3]);
		else
			game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0], game->rc.color[1], game->rc.color[2], game->rc.color[3]);
	}
}