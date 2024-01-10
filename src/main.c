/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/10 16:16:39 by jcario           ###   ########.fr       */
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

void key_loop(void* param)
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

void	end(t_game *game)
{
	(void)game;
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
	t_game			game;

	init_map("maps/map.txt", &game);
	game.rc.dir.x = -0.5;
	game.rc.dir.y = 0; //initial direction vector
	game.rc.plane.x = 0;
	game.rc.plane.y = 0.90; //the 2d raycaster version of camera plane
	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	raycasting(&game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop_hook(game.mlx, &key_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
