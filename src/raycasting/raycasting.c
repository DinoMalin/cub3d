/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:10:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 21:34:28 by jcario           ###   ########.fr       */
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
		game->rc.cameraX = 2 * x / (double)WIDTH - 1;
		game->rc.rayDirX = game->rc.dirX + game->rc.planeX * game->rc.cameraX;
		game->rc.rayDirY = game->rc.dirY + game->rc.planeY * game->rc.cameraX;

		//which box of the map we're in
		game->rc.mapX = (int)game->rc.posX;
		game->rc.mapY = (int)game->rc.posY;

		//length of ray from one x or y-side to next x or y-side
		game->rc.deltaDistX = (game->rc.rayDirX == 0) ? 1e30 : fabs(1 / game->rc.rayDirX);
		game->rc.deltaDistY = (game->rc.rayDirY == 0) ? 1e30 : fabs(1 / game->rc.rayDirY);

		game->rc.hit = 0;

		//calculate step and initial sideDist
		if (game->rc.rayDirX < 0)
		{
			game->rc.stepX = -1;
			game->rc.sideDistX = (game->rc.posX - game->rc.mapX) * game->rc.deltaDistX;
		}
		else
		{
			game->rc.stepX = 1;
			game->rc.sideDistX = (game->rc.mapX + 1.0 - game->rc.posX) * game->rc.deltaDistX;
		}
		if (game->rc.rayDirY < 0)
		{
			game->rc.stepY = -1;
			game->rc.sideDistY = (game->rc.posY - game->rc.mapY) * game->rc.deltaDistY;
		}
		else
		{
			game->rc.stepY = 1;
			game->rc.sideDistY = (game->rc.mapY + 1.0 - game->rc.posY) * game->rc.deltaDistY;
		}

		//perform DDA
		while (game->rc.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (game->rc.sideDistX < game->rc.sideDistY)
			{
				game->rc.sideDistX += game->rc.deltaDistX;
				game->rc.mapX += game->rc.stepX;
				game->rc.side = 0;
			}
			else
			{
				game->rc.sideDistY += game->rc.deltaDistY;
				game->rc.mapY += game->rc.stepY;
				game->rc.side = 1;
			}
			//Check if ray has hit a wall
			if (game->map.map[game->rc.mapX][game->rc.mapY] == '1')
				game->rc.hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(game->rc.side == 0)
			game->rc.perpWallDist = (game->rc.sideDistX - game->rc.deltaDistX);
		else
			game->rc.perpWallDist = (game->rc.sideDistY - game->rc.deltaDistY);

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