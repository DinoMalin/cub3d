/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:52:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 19:54:21 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define WIDTH 1200
# define HEIGHT 675
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.04

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

typedef struct	s_raycast
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		drawStart;
	int		drawEnd;
	int		lineHeight;
} t_raycast;

typedef struct s_map
{
	char	**map;
} t_map;

typedef struct	s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_raycast	rc;
} t_game;

typedef struct s_coordinates
{
	float	x;
	float	y;
} t_coordinates;

typedef struct s_player
{
	t_coordinates coords;
} t_player;

int	init_map(char *name, t_game *game);

#endif