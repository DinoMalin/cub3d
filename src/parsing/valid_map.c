/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:17:23 by jcario            #+#    #+#             */
/*   Updated: 2024/01/18 19:43:22 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
