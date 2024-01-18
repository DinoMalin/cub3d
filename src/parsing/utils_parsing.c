/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:13:16 by jcario            #+#    #+#             */
/*   Updated: 2024/01/18 19:41:51 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*extract_texture(char *line)
{
	char	**split;
	char	*result;

	split = ft_split(line, ' ');
	if (size_matrix(split) != 2)
	{
		free_matrix(split);
		return (NULL);
	}
	result = ft_strdup(split[1]);
	free_matrix(split);
	return (result);
}

void	extract_textures(t_game *game, char	*line)
{
	if (!ft_strncmp("NO ", line, 3))
		game->map.north_texture = extract_texture(line);
	if (!ft_strncmp("SO ", line, 3))
		game->map.south_texture = extract_texture(line);
	if (!ft_strncmp("WE ", line, 3))
		game->map.west_texture = extract_texture(line);
	if (!ft_strncmp("EA ", line, 3))
		game->map.east_texture = extract_texture(line);
	if (!ft_strncmp("F ", line, 2))
		game->map.floor_texture = extract_texture(line);
	if (!ft_strncmp("C ", line, 2))
		game->map.ceiling_texture = extract_texture(line);
}

int	is_map(char *line)
{
	return (ft_strncmp("NO", line, 2) && ft_strncmp("SO", line, 2)
		&& ft_strncmp("WE", line, 2) && ft_strncmp("EA", line, 2)
		&& ft_strncmp("C", line, 1) && ft_strncmp("F", line, 1)
		&& ft_strlen(line) != 0);
}