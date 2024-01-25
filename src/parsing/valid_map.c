/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:17:23 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 16:05:26 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_args(int ac, char **av, t_game *game)
{
	if (ac != 2 || !valid_ext(av[1]))
	{
		if (ac == 3 && !ft_strcmp(av[2], "drunk_mode") && valid_ext(av[1]))
			game->drunk = 1;
		else
		{
			ft_putstr_fd("Error : No map detected.\n", 2);
			return (0);
		}
	}
	return (1);
}

int	is_valid(t_game *game, char **map)
{
	if (!is_closed(map))
	{
		ft_putstr_fd("Error : Map is not closed.\n", 2);
		return (FALSE);
	}
	if (!forbidden_character(map))
	{
		ft_putstr_fd("Error : Map contains forbidden characters.\n", 2);
		return (FALSE);
	}
	if (wrong_starting_pos(map))
	{
		ft_putstr_fd("Error : Wrong starting position.\n", 2);
		return (FALSE);
	}
	if (!textures_defined(game))
	{
		ft_putstr_fd("Error : Miss at least one texture definition.\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
