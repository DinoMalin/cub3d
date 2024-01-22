/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/22 17:10:59 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

# define mapWidth 24
# define mapHeight 24

void	mouse(t_game *game)
{
	int	x;
	int	y;
	
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x > WIDTH / 2)
		rotate_right(game, SENSIBILITY);
	else if (x < WIDTH / 2)
		rotate_left(game, SENSIBILITY);
	if (x != WIDTH / 2)
		mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}

void	key_loop(void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
		up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, ROTATION_SPEED);
	mouse(game);
	process_raycasting(game);
}

void	end(t_game *game)
{
	int	i;

	i = -1;
	while (game->map.map[++i])
		free(game->map.map[i]);
	free(game->map.map);
	i = -1;
	while (++i < 6)
		mlx_delete_texture(game->textures.textures[i]);
	// mlx_delete_texture(game->textures.ceiling);
	// mlx_delete_texture(game->textures.floor);
	mlx_delete_texture(game->textures.sword);
	mlx_delete_texture(game->textures.cursor);
	mlx_delete_texture(game->textures.hotbar);
	mlx_delete_image(game->mlx, game->textures.sword_img);
	mlx_delete_image(game->mlx, game->textures.cursor_img);
	mlx_delete_image(game->mlx, game->textures.hotbar_img);
	// mlx_delete_texture(game->textures.north_wall);
	mlx_terminate(game->mlx);
	// (void)game;
	exit(0);
}

void	keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		end(game);
	if (keydata.key == MLX_KEY_E)
		open_doors(game);
	if (keydata.key == MLX_KEY_R)
		close_doors(game);

}

int main(int ac, char **av)
{
	static t_game	game = {};

	if (ac != 2 || !valid_extension(av[1]))
	{
		ft_putstr_fd("Error : No map detected.\n", 2);
		return (0);
	}
	init_map(av[1], &game);
	if (!is_valid(&game, game.map.map))
		return (0);
	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	init_raycasting(&game);
	process_raycasting(&game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop_hook(game.mlx, &key_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
