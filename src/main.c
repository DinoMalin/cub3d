/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/24 17:12:14 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

# define mapWidth 24
# define mapHeight 24

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
		if (game->textures.index == 4)
		{
			game->textures.play_animation = FALSE;
			game->textures.index = 0;
		}
		else
			game->textures.index++;
		game->textures.sword[game->textures.index]->enabled = true;
		if (game->textures.index == 0)
			game->textures.sword[4]->enabled = false;
		else
			game->textures.sword[game->textures.index - 1]->enabled = false;
	}
	count++;
}

void	key_loop(void* param)
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, ROTATION_SPEED);
	minimap_handler(game);
	cursor(game);
	process_raycasting(game);
	if (game->textures.play_animation)
		handle_sprite(game);
}

void	free_textures(t_game *game)
{
	free(game->map.ceiling_texture);
	free(game->map.floor_texture);
	free(game->map.north_texture);
	free(game->map.west_texture);
	free(game->map.east_texture);
	free(game->map.south_texture);
}

void	end(t_game *game, int valid)
{
	int	i;

	i = -1;
	while (game->map.map[++i])
		free(game->map.map[i]);
	free(game->map.map);
	i = -1;
	free_textures(game);
	if (!valid)
		exit(0);
	while (++i < 6)
		mlx_delete_texture(game->textures.textures[i]);
	i = -1;
	while (++i < 5)
		mlx_delete_image(game->mlx, game->textures.sword[i]);
	mlx_delete_image(game->mlx, game->textures.cursor);
	mlx_delete_image(game->mlx, game->textures.hotbar);
	mlx_delete_texture(game->textures.ceiling);
	mlx_delete_texture(game->textures.floor);
	mlx_terminate(game->mlx);
	exit(0);
}

void	keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		end(game, 1);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		destroy_block(game);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		game->map.cast_minimap = !game->map.cast_minimap;
}

void	mouse(mouse_key_t but, action_t action, modifier_key_t mod, void* param)
{
	t_game *game;

	(void)mod;
	game = (t_game *)param;
	if (but == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		game->textures.play_animation = TRUE;
		destroy_block(game);
	}
	else if (but == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		place_block(game);
}

int main(int ac, char **av)
{
	static t_game	game = {};

	handle_args(ac, av, &game);
	init_map(av[1], &game);
	if (!handle_args(ac, av, &game) || !is_valid(&game, game.map.map))
		end(&game, 0);
	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	init_raycasting(&game);
	process_raycasting(&game);
	init_sword(&game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop_hook(game.mlx, &key_loop, &game);
	mlx_mouse_hook(game.mlx, mouse, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
