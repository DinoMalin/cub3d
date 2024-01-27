/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:31:10 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 15:58:43 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_buffer(t_game *game, mlx_image_t *image)
{
	int	x;
	int	y;

	y = 0;
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

void	calculate_texture(t_game *game, int x)
{
	if (!game->rc.side)
		game->rc.pwall_dist = (game->rc.side_dist.x - game->rc.delta_dist.x);
	else
		game->rc.pwall_dist = (game->rc.side_dist.y - game->rc.delta_dist.y);
	game->rc.line_height = (int)(HEIGHT / game->rc.pwall_dist);
	game->rc.draw_start = -game->rc.line_height / 2 + HEIGHT / 2;
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0;
	game->rc.draw_end = game->rc.draw_start + game->rc.line_height;
	if (game->rc.draw_end >= HEIGHT)
		game->rc.draw_end = HEIGHT - 1;
	if (!game->rc.side)
		game->rc.wallx = game->rc.pos.y + game->rc.pwall_dist * game->rc.ray.y;
	else
		game->rc.wallx = game->rc.pos.x + game->rc.pwall_dist * game->rc.ray.x;
	game->rc.wallx -= floor(game->rc.wallx);
	game->rc.texx = (int)(game->rc.wallx * (double)game->textures.textures
		[game->rc.tex_num]->width);
	get_tex_x(game);
	game->rc.step_texture = 1.0 * game->textures.textures
	[game->rc.tex_num]->height / game->rc.line_height;
	game->rc.tex_pos = (game->rc.draw_start - HEIGHT / 2
			+ game->rc.line_height / 2) * game->rc.step_texture;
	draw_texture(x, game);
}

void	draw_texture(int x, t_game *game)
{
	int	y;
	int	texy;

	y = game->rc.draw_start - 1;
	while (++y < game->rc.draw_end)
	{
		texy = (int)game->rc.tex_pos & (game->textures.textures
			[game->rc.tex_num]->height - 1);
		game->rc.tex_pos += game->rc.step_texture;
		game->rc.color = &game->textures.textures[game->rc.tex_num]->pixels
		[(game->textures.textures[game->rc.tex_num]->height
				* texy + game->rc.texx) * 4];
		game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0],
				game->rc.color[1], game->rc.color[2], game->rc.color[3]);
	}
}
