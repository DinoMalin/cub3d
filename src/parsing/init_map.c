/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:02:50 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 16:05:00 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	get_starting_position(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map.map[x])
	{
		y = 0;
		while (game->map.map[x][y])
		{
			if (ft_strchr("NSEW", game->map.map[x][y]))
			{
				game->rc.pos.x = x;
				game->rc.pos.y = y;
				game->map.starting_direction = game->map.map[x][y];
				return ;
			}
			y++;
		}
		x++;
	}
}

int	end_init(int fd, char *line, t_game *game)
{
	close(fd);
	free(line);
	get_starting_position(game);
	init_size_map(game);
	return (TRUE);
}

int	check_line(t_game *game, char *line)
{
	if (line)
	{
		init_map_properties(&game->map);
		return (TRUE);
	}
	return (FALSE);
}

int	init_map(t_game *game, char *name)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	line = get_next_line(fd);
	if (!check_line(game, line))
		return (FALSE);
	while (line)
	{
		if (ft_strlen(line) > 1)
		{
			temp = line;
			line = ft_strtrim(line, "\n");
			free(temp);
			if (is_map(line))
				game->map.map = join_matrix(game->map.map, line);
			extract_textures(game, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (end_init(fd, line, game));
}
