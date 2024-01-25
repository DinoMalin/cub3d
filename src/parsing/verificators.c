/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:15:55 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 12:45:46 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	valid_ext(char *str)
{
	int	i;

	i = ft_strlen(str);
	i -= ft_strlen(".cub");
	if (i <= 0)
		return (FALSE);
	return !ft_strcmp(".cub", str + i);
}

int	is_closed(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("0NEWSD", map[i][j]) && (!map[i + 1] || i == 0))
				return (FALSE);
			if (ft_strchr("0NEWSD", map[i][j]) && (!map[i][j + 1] || j == 0))
				return (FALSE);
			if (ft_strchr("0NEWSD", map[i][j])
				&& (int)ft_strlen(map[i - 1]) - 1 < j)
				return (FALSE);
			if (ft_strchr("0NEWSD", map[i][j])
				&& (!ft_strchr("10NEWSD", map[i][j + 1])
				|| !ft_strchr("10NEWSD", map[i][j - 1])
				|| !ft_strchr("10NEWSD", map[i + 1][j])
				|| !ft_strchr("10NEWSD", map[i - 1][j])))
				return (FALSE);
		}
	}
	return (TRUE);
}

int	forbidden_character(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!ft_strchr("10NEWSD ", map[i][j]))
				return (FALSE);
	}
	return (TRUE);
}

int	wrong_starting_pos(char **map)
{
	int	i;
	int	j;
	int	starting_pos;

	i = -1;
	starting_pos = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (ft_strchr("NEWS", map[i][j]))
				starting_pos++;
	}
	return (starting_pos != 1);
}

int	textures_defined(t_game *game)
{
	return (game->map.north_texture && game->map.south_texture
		&& game->map.east_texture && game->map.west_texture
		&& game->map.floor_texture && game->map.ceiling_texture);
}
