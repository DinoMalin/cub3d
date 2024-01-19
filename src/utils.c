/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:06:04 by jcario            #+#    #+#             */
/*   Updated: 2024/01/19 20:02:25 by jcario           ###   ########.fr       */
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

void	open_doors(t_game *game)
{
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == 'D')
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = 'O';
	if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] == 'D')
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = 'O';
	if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == 'D')
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = 'O';
	if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] == 'D')
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = 'O';
}

void	close_doors(t_game *game)
{
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == 'O')
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = 'D';
	if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] == 'O')
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = 'D';
	if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == 'O')
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = 'D';
	if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] == 'O')
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = 'D';
}