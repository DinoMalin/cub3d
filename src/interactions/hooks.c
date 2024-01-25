/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:00:34 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 17:06:24 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	cursor(t_game *game)
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

void	handle_sprite(t_game *game)
{
	static int	count = 0;

	if (count > 100)
		count = 0;
	if (count % 2)
	{
		if (game->img.index == 4)
		{
			game->img.play_animation = FALSE;
			game->img.index = 0;
		}
		else
			game->img.index++;
		game->img.sword[game->img.index]->enabled = true;
		if (game->img.index == 0)
			game->img.sword[4]->enabled = false;
		else
			game->img.sword[game->img.index - 1]->enabled = false;
	}
	count++;
}

void	key_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, ROTATION_SPEED);
	minimap_handler(game);
	cursor(game);
	process_raycasting(game);
	if (game->img.play_animation)
		handle_sprite(game);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		end(game, 2);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		destroy_block(game);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		game->map.cast_minimap = !game->map.cast_minimap;
}

void	mouse(mouse_key_t but, action_t at, modifier_key_t md, void *param)
{
	t_game	*game;

	(void)md;
	game = (t_game *)param;
	if (but == MLX_MOUSE_BUTTON_LEFT && at == MLX_PRESS)
		destroy_block(game);
	else if (but == MLX_MOUSE_BUTTON_RIGHT && at == MLX_PRESS)
		place_block(game);
}
