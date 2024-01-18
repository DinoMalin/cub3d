/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:15:55 by jcario            #+#    #+#             */
/*   Updated: 2024/01/18 12:44:16 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	valid_extension(char *str)
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
				&& (!ft_strchr("10NEWSD", map[i][j + 1])
				|| !ft_strchr("10NEWSD", map[i][j - 1])
				|| !ft_strchr("10NEWSD", map[i + 1][j])
				|| !ft_strchr("10NEWSD", map[i - 1][j])))
				return (FALSE);
		}
	}
	return (TRUE);
}

int	forbidden_character(char	**map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!ft_strchr("10NEWSD", map[i][j]))
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
			if (ft_strchr("NEWSD", map[i][j]))
				starting_pos++;
	}
	return (starting_pos != 1);
}

int	get_textures(t_game *game, char	**map)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		if (!ft_strncmp("NO ", map[i], 3))
			game->map.north_texture = extract_texture(map[i]);
		if (!ft_strncmp("SO ", map[i], 3))
			game->map.south_texture = extract_texture(map[i]);
		if (!ft_strncmp("WE ", map[i], 3))
			game->map.west_texture = extract_texture(map[i]);
		if (!ft_strncmp("EA ", map[i], 3))
			game->map.east_texture = extract_texture(map[i]);
		if (!ft_strncmp("F ", map[i], 2))
			game->map.floor_texture = extract_texture(map[i]);
		if (!ft_strncmp("C ", map[i], 2))
			game->map.ceiling_texture = extract_texture(map[i]);
	}
	return (game->map.north_texture && game->map.south_texture
		&& game->map.east_texture && game->map.west_texture
		&& game->map.floor_texture && game->map.ceiling_texture);
}
