/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:10:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/10 16:18:18 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

mlx_image_t	*dda(t_game *game)
{
	mlx_image_t *image;
	
	image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	fill_image(image);

	for (int x = 0; x < WIDTH; x++)
	{
		game->rc.camera.x = 2 * x / (double)WIDTH - 1;
		game->rc.rayDir.x = game->rc.dir.x + game->rc.plane.x * game->rc.camera.x;
		game->rc.rayDir.y = game->rc.dir.y + game->rc.plane.y * game->rc.camera.x;

		//which box of the map we're in
		game->rc.mapPos.x = (int)game->rc.pos.x;
		game->rc.mapPos.y = (int)game->rc.pos.y;

		//length of ray from one x or y-side to next x or y-side
		game->rc.deltaDist.x = (game->rc.rayDir.x == 0) ? 1e30 : fabs(1 / game->rc.rayDir.x);
		game->rc.deltaDist.y = (game->rc.rayDir.y == 0) ? 1e30 : fabs(1 / game->rc.rayDir.y);

		game->rc.hit = 0;

		//calculate step and initial sideDist
		if (game->rc.rayDir.x < 0)
		{
			game->rc.step.x = -1;
			game->rc.sideDist.x = (game->rc.pos.x - game->rc.mapPos.x) * game->rc.deltaDist.x;
		}
		else
		{
			game->rc.step.x = 1;
			game->rc.sideDist.x = (game->rc.mapPos.x + 1.0 - game->rc.pos.x) * game->rc.deltaDist.x;
		}
		if (game->rc.rayDir.y < 0)
		{
			game->rc.step.y = -1;
			game->rc.sideDist.y = (game->rc.pos.y - game->rc.mapPos.y) * game->rc.deltaDist.y;
		}
		else
		{
			game->rc.step.y = 1;
			game->rc.sideDist.y = (game->rc.mapPos.y + 1.0 - game->rc.pos.y) * game->rc.deltaDist.y;
		}

		//perform DDA
		while (game->rc.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (game->rc.sideDist.x < game->rc.sideDist.y)
			{
				game->rc.sideDist.x += game->rc.deltaDist.x;
				game->rc.mapPos.x += game->rc.step.x;
				game->rc.side = 0;
			}
			else
			{
				game->rc.sideDist.y += game->rc.deltaDist.y;
				game->rc.mapPos.y += game->rc.step.y;
				game->rc.side = 1;
			}
			//Check if ray has hit a wall
			if (game->map.map[game->rc.mapPos.x][game->rc.mapPos.y] == '1')
				game->rc.hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(game->rc.side == 0)
			game->rc.perpWallDist = (game->rc.sideDist.x - game->rc.deltaDist.x);
		else
			game->rc.perpWallDist = (game->rc.sideDist.y - game->rc.deltaDist.y);

		//Calculate height of line to draw on screen
		game->rc.lineHeight = (int)(HEIGHT / game->rc.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		game->rc.drawStart = -game->rc.lineHeight / 2 + HEIGHT / 2;
		if(game->rc.drawStart < 0)
			game->rc.drawStart = 0;
		game->rc.drawEnd = game->rc.lineHeight / 2 + HEIGHT / 2;
		if(game->rc.drawEnd >= HEIGHT)
			game->rc.drawEnd = HEIGHT - 1;

		uint32_t color = WALL_1;
		if (game->rc.side == 1)
			color = WALL_2;
		vertical_line(game->rc.drawStart, game->rc.drawEnd, x, image, color);
	}
	return (image);
}

void	raycasting(t_game *game)
{
	static int count = 0;
	static mlx_image_t *current_img;

	if (count > 0)
		mlx_delete_image(game->mlx, current_img);
	current_img = dda(game);
	mlx_image_to_window(game->mlx, current_img, 0, 0);
	count++;
}