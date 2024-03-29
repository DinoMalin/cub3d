/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:52:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/26 13:50:44 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define WIDTH 1200
# define HEIGHT 675
# define MOVE_SPEED 0.08
# define ROTATION_SPEED 0.05
# define SENSIBILITY 0.08

# define PI	3.141592653

# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "MLX42.h"

typedef struct s_images
{
	mlx_image_t		*sword[5];
	mlx_image_t		*hotbar;
	mlx_image_t		*cursor;
	int				index;
	int				play_animation;
}	t_images;

typedef struct s_textures
{
	mlx_texture_t	*floor;
	mlx_texture_t	*ceiling;
	mlx_texture_t	*textures[6];
}	t_textures;

typedef struct s_double_coordinates
{
	double	x;
	double	y;
}	t_double_coords;

typedef struct s_int_coordinates
{
	int	x;
	int	y;
}	t_int_coords;

typedef struct s_raycast
{
	/* === WALL CASTING === */
	t_double_coords	pos;
	t_double_coords	dir;
	t_double_coords	plane;
	t_double_coords	camera;
	t_double_coords	ray;
	t_double_coords	side_dist;
	t_double_coords	delta_dist;
	t_int_coords	map_pos;
	t_int_coords	step;
	double			pwall_dist;
	double			step_texture;
	double			tex_pos;
	int				hit;
	int				side;
	int				draw_start;
	int				draw_end;
	int				line_height;
	double			wallx;
	int				texx;
	int				tex_num;
	int				is_door;

	/* === FLOOR AND CEILING CASTING === */
	t_double_coords	ray0;
	t_double_coords	ray1;
	int				p;
	float			pos_z;
	float			row_distance;
	t_double_coords	floor_step;
	t_double_coords	floor;
	t_int_coords	cell;
	t_int_coords	texture;

	/* === GENERAL === */
	uint8_t			*color;
	uint32_t		screen_buffer[WIDTH][HEIGHT];
}	t_raycast;

typedef struct s_map
{
	char		**map;
	char		starting_direction;
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	char		*floor_texture;
	char		*ceiling_texture;
	int			width;
	int			height;
	int			cast_minimap;
	mlx_image_t	*minimap;
	int			ratio;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_raycast	rc;
	t_textures	textures;
	t_images	img;
	int			drunk;
}	t_game;

/* ======== GUI ======== */

void		load_textures(t_game *game);
void		set_gui(t_game *game);
void		init_sword(t_game *game);

void		create_minimap(t_game *game);
void		minimap_handler(t_game *game);

/* ======== INTERACTIONS ======== */

void		destroy_block(t_game *game);
void		place_block(t_game *game);

void		cursor(t_game *game);
void		handle_sprite(t_game *game);
void		key_loop(void *param);
void		keyhook(mlx_key_data_t keydata, void *param);
void		mouse(mouse_key_t but, action_t at, modifier_key_t md, void *param);

/* ======== INIT ======== */

int			init_map(t_game *game, char *name);	
void		init_raycasting(t_game *game);
void		get_starting_direction(t_game *game);
void		init_floor_ceiling_casting(int y, t_game *game);
void		init_walls_casting(int x, t_game *game);

/* ======== UTILS ======== */

void		cross(void *param);
void		end(t_game *game, int error_code);
mlx_image_t	*load_image(t_game *game, const char *path);
void		free_matrix(char **matrix);
int			len_matrix(char **arr);

/* ======== RAYCASTING ======== */

void		process_raycasting(t_game *game);
void		calculate_texture(t_game *game, int x);
void		draw_texture(int x, t_game *game);
void		draw_buffer(t_game *game, mlx_image_t *image);
void		clear_buffer(t_game *game);
int			get_rgba(int r, int g, int b, int a);

void		rotate_left(t_game *game, double rotation_angle);
void		rotate_right(t_game *game, double rotation_angle);
double		get_rotation_angle(t_game *game);
void		up(t_game *game);
void		down(t_game *game);
void		right(t_game *game);
void		left(t_game *game);

void		get_floor_texture(t_game *game, int x, int y);
void		get_adequate_texture(t_game *game);
void		get_door_texture(t_game *game);
void		get_tex_x(t_game *game);

/* ======== PARSING ======== */

int			is_valid(t_game *game, char **map);
int			handle_args(int ac, char **av, t_game *game);

int			valid_ext(char *str);
int			is_closed(char **map);
int			forbidden_character(char **map);
int			wrong_starting_pos(char **map);
int			textures_defined(t_game *game);

int			is_map(char *line);
void		init_size_map(t_game *game);
void		extract_textures(t_game *game, char	*line);
void		init_map_properties(t_map *map);

#endif