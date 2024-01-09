/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 19:53:55 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

# define mapWidth 24
# define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// int ft_abs(int x)
// {
// 	if (x < 0)
// 		return (-x);
// 	return (x);
// }

int32_t get_color(int32_t red, int32_t green, int32_t blue, int32_t a)
{
	return (red << 24 | green << 16 | blue << 8 | a);
}

void	vertical_line(int start_y, int end_y, int x, mlx_image_t *image, uint32_t color)
{
	while (start_y <= end_y)
	{
		mlx_put_pixel(image, x, start_y, color);
		start_y++;
	}
}

void	fill_image(mlx_image_t *image)
{
	int	x;

	x = 0;
	// Ceiling
	while (x < WIDTH)
	{
		vertical_line(0, HEIGHT / 2, x, image, 0xc4fffeff);
		x++;
	}
	// Floor
	x = 0;
	while (x < WIDTH)
	{
		vertical_line(HEIGHT / 2, HEIGHT - 1, x, image, 0xcca37cff);
		x++;
	}
}

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

		uint32_t color = 0x73FF75FF;
		if (game->rc.side == 1)
			color = 0x419143FF;
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

void keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;
	if (keydata.key ==  MLX_KEY_A)
	{
		double	oldDirX = game->rc.dirX;
		double	oldPlaneX = game->rc.planeX;
		game->rc.dirX = game->rc.dirX * cos(ROTATION_SPEED) - game->rc.dirY * sin(ROTATION_SPEED);
		game->rc.dirY = oldDirX * sin(ROTATION_SPEED) + game->rc.dirY * cos(ROTATION_SPEED);
		game->rc.planeX = game->rc.planeX * cos(ROTATION_SPEED) - game->rc.planeY * sin(ROTATION_SPEED);
		game->rc.planeY = oldPlaneX * sin(ROTATION_SPEED) + game->rc.planeY * cos(ROTATION_SPEED);
	}
	if (keydata.key ==  MLX_KEY_D)
	{
		double	oldDirX = game->rc.dirX;
		double	oldPlaneX = game->rc.planeX;
		game->rc.dirX = game->rc.dirX * cos(-ROTATION_SPEED) - game->rc.dirY * sin(-ROTATION_SPEED);
		game->rc.dirY = oldDirX * sin(-ROTATION_SPEED) + game->rc.dirY * cos(-ROTATION_SPEED);
		game->rc.planeX = game->rc.planeX * cos(-ROTATION_SPEED) - game->rc.planeY * sin(-ROTATION_SPEED);
		game->rc.planeY = oldPlaneX * sin(-ROTATION_SPEED) + game->rc.planeY * cos(-ROTATION_SPEED);
	}
	if (keydata.key == MLX_KEY_W)
	{
		if(game->map.map[(int)(game->rc.posX + game->rc.dirX * MOVE_SPEED)][(int)game->rc.posY] != '1')
			game->rc.posX += game->rc.dirX * MOVE_SPEED;
		if(game->map.map[(int)game->rc.posX][(int)(game->rc.posY + game->rc.dirY * MOVE_SPEED)] != '1')
			game->rc.posY += game->rc.dirY * MOVE_SPEED;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if(game->map.map[(int)(game->rc.posX - game->rc.dirX * MOVE_SPEED)][(int)game->rc.posY] != '1')
			game->rc.posX -= game->rc.dirX * MOVE_SPEED;
		if(game->map.map[(int)game->rc.posX][(int)(game->rc.posY - game->rc.dirY * MOVE_SPEED)] != '1')
			game->rc.posY -= game->rc.dirY * MOVE_SPEED;
	}
	raycasting(game);
}

int main()
{
	t_game			game;

	init_map("maps/map.txt", &game);
	game.rc.dirX = -1;
	game.rc.dirY = 0; //initial direction vector
	game.rc.planeX = 0;
	game.rc.planeY = 0.66; //the 2d raycaster version of camera plane
	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	raycasting(&game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
