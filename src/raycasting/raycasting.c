/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:10:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/13 02:10:21 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_raycasting(t_game *game)
{
	game->rc.dir.x = -0.5;
	game->rc.dir.y = 0;
	game->rc.plane.x = 0;
	game->rc.plane.y = 0.90;
	// game->textures.north_wall = mlx_load_png("../textures/tile32");
	game->textures.north_wall = mlx_load_png("./textures/cobblestone.png");
	game->textures.floor = mlx_load_png("./textures/plank.png");
	game->textures.ceiling = mlx_load_png("./textures/plank.png");
	if (!game->textures.north_wall)
		ft_printf("error");
}

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
			// ft_printf("x : %d y :%d\n", x, y);
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

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

mlx_image_t	*dda(t_game *game)
{
	mlx_image_t *image;
	
	image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	// fill_image(image);

	//FLOOR / CEILING CASTING
	for(int y = 0; y < HEIGHT; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = game->rc.dir.x - game->rc.plane.x;
		float rayDirY0 = game->rc.dir.y - game->rc.plane.y;
		float rayDirX1 = game->rc.dir.x + game->rc.plane.x;
		float rayDirY1 = game->rc.dir.y + game->rc.plane.y;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - HEIGHT / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * HEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = game->rc.pos.x + rowDistance * rayDirX0;
		float floorY = game->rc.pos.y + rowDistance * rayDirY0;

		for(int x = 0; x < WIDTH; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(game->textures.floor->width * (floorX - cellX)) & (game->textures.floor->width - 1);
			int ty = (int)(game->textures.floor->height * (floorY - cellY)) & (game->textures.floor->height - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// floor
			game->rc.color = &game->textures.floor->pixels[(game->textures.floor->width * ty + tx) * 4];
			game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0], game->rc.color[1], game->rc.color[2], game->rc.color[3]);

			//ceiling (symmetrical, at HEIGHT - y - 1 instead of y)
			game->rc.color = &game->textures.ceiling->pixels[(game->textures.floor->width * ty + tx) * 4];
			game->rc.screen_buffer[x][HEIGHT - y - 1] = get_rgba(game->rc.color[0], game->rc.color[1], game->rc.color[2], game->rc.color[3]);
		}
	}

	// WALL CASTING
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

		// int texNum = game->map.map[game->rc.mapPos.x][game->rc.mapPos.y] - '1';
		double wallX;
		if (game->rc.side == 0)
			wallX = game->rc.pos.y + game->rc.perpWallDist * game->rc.rayDir.y;
		else
			wallX = game->rc.pos.x + game->rc.perpWallDist * game->rc.rayDir.x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)game->textures.north_wall->width);
		if (game->rc.side == 0 && game->rc.rayDir.x > 0)
			texX = game->textures.north_wall->width - texX - 1;
		if (game->rc.side == 1  && game->rc.rayDir.y < 0)
			texX = game->textures.north_wall->width - texX - 1;

		game->rc.step_texture = 1.0 * game->textures.north_wall->height / game->rc.lineHeight;
		game->rc.texPos = (game->rc.drawStart - HEIGHT / 2 + game->rc.lineHeight / 2) * game->rc.step_texture;
		for (int y = game->rc.drawStart; y < game->rc.drawEnd; y++)
		{
			int texY = (int)game->rc.texPos & (game->textures.north_wall->height - 1);
			game->rc.texPos += game->rc.step_texture;
			game->rc.color = &game->textures.north_wall->pixels[(game->textures.north_wall->height * texY + texX) * 4];
			if (game->rc.side)
				game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0] / 2, game->rc.color[1] / 2, game->rc.color[2] / 2, game->rc.color[3]);
			else
				game->rc.screen_buffer[x][y] = get_rgba(game->rc.color[0], game->rc.color[1], game->rc.color[2], game->rc.color[3]);
		}
	}
	draw_buffer(game, image);
	clear_buffer(game);
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