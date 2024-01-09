/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 22:28:26 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

# define mapWidth 24
# define mapHeight 24

void	game_loop(void *param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (game->controls.left)
		left(game);
	if (game->controls.right)
		right(game);
	if (game->controls.up)
		up(game);
	if (game->controls.down)
		down(game);
}

void keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	// if (keydata.key ==  MLX_KEY_A && keydata.action == MLX_PRESS)
	// 	game->controls.left = true;
	// if (keydata.key ==  MLX_KEY_D && keydata.action == MLX_PRESS)
	// 	game->controls.right = true;
	// if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	// 	game->controls.up = true;
	// if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	// 	game->controls.down = true;
	// if (keydata.key ==  MLX_KEY_A && keydata.action == MLX_RELEASE)
	// 	game->controls.left = false;
	// if (keydata.key ==  MLX_KEY_D && keydata.action == MLX_RELEASE)
	// 	game->controls.right = false;
	// if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
	// 	game->controls.up = false;
	// if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
	// 	game->controls.down = false;
	if (keydata.key == MLX_KEY_W)
		up(game);
	if (keydata.key == MLX_KEY_A)
		left(game);
	if (keydata.key == MLX_KEY_S)
		down(game);
	if (keydata.key == MLX_KEY_D)
		right(game);
	raycasting(game);
}

int main()
{
	t_game			game;

	init_map("maps/map.txt", &game);
	game.rc.dirX = -0.5;
	game.rc.dirY = 0; //initial direction vector
	game.rc.planeX = 0;
	game.rc.planeY = 0.90; //the 2d raycaster version of camera plane
	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	raycasting(&game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	// mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
