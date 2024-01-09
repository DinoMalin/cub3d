/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 18:29:57 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

# define mapWidth 24
# define mapHeight 24
# define screenWidth 1000
# define screenHeight 560
# define moveSpeed 0.5
# define rotSpeed 0.05

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

typedef struct s_raycast
{
	mlx_t *mlx;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
} t_raycast;

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
	while (x < screenWidth)
	{
		vertical_line(0, screenHeight / 2, x, image, 0xc4fffeff);
		x++;
	}
	// Floor
	x = 0;
	while (x < screenWidth)
	{
		vertical_line(screenHeight / 2, screenHeight - 1, x, image, 0xcca37cff);
		x++;
	}
}

void	raycasting(mlx_t *mlx, t_raycast *rc)
{
	mlx_image_t *image;
	
	image = mlx_new_image(mlx, screenWidth, screenHeight);
	fill_image(image);

	for (int x = 0; x < screenWidth; x++)
	{
		double cameraX = 2 * x / (double)screenWidth - 1;
		double rayDirX = rc->dirX + rc->planeX * cameraX;
		double rayDirY = rc->dirY + rc->planeY * cameraX;


		//which box of the map we're in
		int mapX = (int)rc->posX;
		int mapY = (int)rc->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rc->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rc->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rc->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rc->posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		uint32_t color = 0x73FF75FF;
		if (side == 1)
			color = 0x419143FF;
		vertical_line(drawStart, drawEnd, x, image, color);
	}
	mlx_image_to_window(mlx, image, 0, 0);
}

void keyhook(mlx_key_data_t keydata, void* param)
{
	t_raycast *rc = (t_raycast *)param;
	if (keydata.key ==  MLX_KEY_A)
	{
		double	oldDirX = rc->dirX;
		double	oldPlaneX = rc->planeX;
		rc->dirX = rc->dirX * cos(rotSpeed) - rc->dirY * sin(rotSpeed);
		rc->dirY = oldDirX * sin(rotSpeed) + rc->dirY * cos(rotSpeed);
		rc->planeX = rc->planeX * cos(rotSpeed) - rc->planeY * sin(rotSpeed);
		rc->planeY = oldPlaneX * sin(rotSpeed) + rc->planeY * cos(rotSpeed);
	}
	if (keydata.key ==  MLX_KEY_D)
	{
		double	oldDirX = rc->dirX;
		double	oldPlaneX = rc->planeX;
		rc->dirX = rc->dirX * cos(-rotSpeed) - rc->dirY * sin(-rotSpeed);
		rc->dirY = oldDirX * sin(-rotSpeed) + rc->dirY * cos(-rotSpeed);
		rc->planeX = rc->planeX * cos(-rotSpeed) - rc->planeY * sin(-rotSpeed);
		rc->planeY = oldPlaneX * sin(-rotSpeed) + rc->planeY * cos(-rotSpeed);
	}
	if (keydata.key == MLX_KEY_W)
	{
		if(worldMap[(int)(rc->posX + rc->dirX * moveSpeed)][(int)rc->posY] == 0)
			rc->posX += rc->dirX * moveSpeed;
		if(worldMap[(int)rc->posX][(int)(rc->posY + rc->dirY * moveSpeed)] == 0)
			rc->posY += rc->dirY * moveSpeed;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if(worldMap[(int)(rc->posX - rc->dirX * moveSpeed)][(int)rc->posY] == 0)
			rc->posX -= rc->dirX * moveSpeed;
		if(worldMap[(int)rc->posX][(int)(rc->posY - rc->dirY * moveSpeed)] == 0)
			rc->posY -= rc->dirY * moveSpeed;
	}
	raycasting(rc->mlx, rc);
}

int main()
{
	t_raycast		rc;

	rc.posX = 22;
	rc.posY = 12;  //x and y start position
	rc.dirX = -1;
	rc.dirY = 0; //initial direction vector
	rc.planeX = 0;
	rc.planeY = 0.66; //the 2d raycaster version of camera plane
	rc.mlx = mlx_init(screenWidth, screenHeight, "dinozaur", TRUE);
	raycasting(rc.mlx, &rc);
	mlx_key_hook(rc.mlx, &keyhook, &rc);
	mlx_loop(rc.mlx);
	mlx_terminate(rc.mlx);
	return (0);
}
