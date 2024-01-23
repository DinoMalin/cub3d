/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:06:04 by jcario            #+#    #+#             */
/*   Updated: 2024/01/23 15:48:54 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	size_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*result;

	texture = mlx_load_png(path);
	result = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	return (result);
}

void	open_doors(t_game *game)
{
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == 'D')
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = '0';
	else if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] == 'D')
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = '0';
	else if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == 'D')
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = '0';
	else if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] == 'D')
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = '0';
}

void	close_doors(t_game *game)
{
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == '0' && game->rc.dir.y >= 0)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = 'D';
	else if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] == '0' && game->rc.dir.y < 0)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = 'D';
	else if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == '0' && game->rc.dir.x >= 0)
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = 'D';
	else if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] == '0' && game->rc.dir.y < 0)
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = 'D';
}