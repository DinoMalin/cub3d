/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:02:50 by jcario            #+#    #+#             */
/*   Updated: 2024/01/05 14:22:58 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_map_properties(t_map *map)
{
	map->map = malloc(sizeof(char *));
	map->map[0] = NULL;
}

int	len_matrix(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

char	**join_matrix(char **s1, char *s2)
{
	char	**result;
	int		len;
	int		i;

	len = len_matrix(s1);
	i = 0;
	result = malloc((len + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = ft_strdup(s1[i]);
		free(s1[i]);
		i++;
	}
	result[i++] = ft_strdup(s2);
	result[i] = NULL;
	free(s1);
	return (result);
}

int	init_map(char *name, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	line = get_next_line(fd);
	if (line)
		init_map_properties(map);
	else
		return (FALSE);
	while (line)
	{
		line = ft_strtrim(line, "\n");
		map->map = join_matrix(map->map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (TRUE);
}