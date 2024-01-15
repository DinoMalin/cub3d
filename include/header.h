/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:52:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/15 17:27:39 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define WIDTH 1200
# define HEIGHT 675
# define MOVE_SPEED 0.08
# define ROTATION_SPEED 0.05

# define WALL_1 0x73FF75FF
# define WALL_2 0x419143FF
# define CEILING 0xc4fffeff
# define FLOOR 0xcca37cff

# define SEGFAULT "[1]    843162 segmentation fault (core dumped)  ./cub3D"

# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "MLX42.h"

typedef	struct s_textures
{
	mlx_texture_t	*floor;
	mlx_texture_t	*ceiling;
	mlx_texture_t	*north_wall;
	mlx_texture_t	*south_wall;
	mlx_texture_t	*west_wall;
	mlx_texture_t	*est_wall;
	mlx_texture_t	*sword;
	mlx_image_t		*sword_img;
} t_textures;


typedef struct	s_double_coordinates
{
	double	x;
	double	y;
} t_double_coords;

typedef struct	s_float_coordinates
{
	float	x;
	float	y;
} t_float_coords;

typedef struct	s_int_coordinates
{
	int	x;
	int	y;
} t_int_coords;

typedef struct	s_raycast
{
	/* === WALL CASTING === */
	t_double_coords	pos;
	t_double_coords	dir;
	t_double_coords	plane;
	t_double_coords	camera;
	t_double_coords	ray;
	t_double_coords	sideDist;
	t_double_coords	deltaDist;
	t_int_coords	mapPos;
	t_int_coords	step;
	double			perpWallDist;
	double			step_texture;
	double			texPos;
	int				hit;
	int				side;
	int				drawStart;
	int				drawEnd;
	int				lineHeight;
	double			wallX;
	int				texX;
	/* === FLOOR AND CEILING CASTING === */
	t_double_coords	ray0;
	t_double_coords	ray1;
	int				p;
	float			posZ;
	float			rowDistance;
	t_double_coords	floorStep;
	t_double_coords	floor;
	t_int_coords	cell;
	t_int_coords	texture;
	/* === GENERAL === */
	uint8_t			*color;
	uint32_t		screen_buffer[WIDTH][HEIGHT];
} t_raycast;

typedef struct s_map
{
	char		**map;
} t_map;

typedef struct s_controls
{
	int	left;
	int	right;
	int	up;
	int	down;
} t_controls;

typedef struct	s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_raycast	rc;
	t_controls	controls;
	t_textures	textures;
} t_game;

/* ======== INIT ======== */
int	init_map(char *name, t_game *game);

/* ======== RAYCASTING ======== */
void	init_raycasting(t_game *game);
void	process_raycasting(t_game *game);

void	init_raycasting(t_game *game);
void	init_floor_ceiling_casting(int y, t_game *game);
void	init_walls_casting(int x, t_game *game);
void	calculate_texture(t_game *game);
void	draw_texture(int x, t_game *game);

void	draw_buffer(t_game *game, mlx_image_t *image);
void	clear_buffer(t_game *game);
int		get_rgba(int r, int g, int b, int a);

void	left(t_game *game);
void	right(t_game *game);
void	up(t_game *game);
void	down(t_game *game);


#endif