/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/16 12:27:51 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

# define mapWidth 24
# define mapHeight 24

void key_loop(void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
		up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		left(game, ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) || mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		right(game, ROTATION_SPEED);
	process_raycasting(game);
}

void	end(t_game *game)
{
	(void)game;
	// ft_printf(SEGFAULT);
	exit(0);
}

void keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		end(game);
}

int main()
{
	static t_game	game = {};

	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	init_map("maps/map.txt", &game);
	init_raycasting(&game);
	process_raycasting(&game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop_hook(game.mlx, &key_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
