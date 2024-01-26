/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/26 13:52:53 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	static t_game	game = {};

	if (!handle_args(ac, av, &game))
		return (0);
	if (!init_map(&game, av[1]))
		return (ft_putstr_fd("No map detected.\n", 2));
	if (!is_valid(&game, game.map.map))
		end(&game, 0);
	game.mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	init_raycasting(&game);
	process_raycasting(&game);
	init_sword(&game);
	mlx_close_hook(game.mlx, cross, &game);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop_hook(game.mlx, &key_loop, &game);
	mlx_mouse_hook(game.mlx, mouse, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
