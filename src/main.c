/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/10 15:00:36 by jcario           ###   ########.fr       */
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

void keyhook(void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
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
	// mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop_hook(game.mlx, &keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
