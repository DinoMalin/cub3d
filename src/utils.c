/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:06:04 by jcario            #+#    #+#             */
/*   Updated: 2024/01/24 14:22:59 by jcario           ###   ########.fr       */
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

double get_rotation_angle(t_game *game)
{
	double radians;
	double degrees;
	
	radians = atan2(game->rc.dir.y, game->rc.dir.x);
	degrees = radians * (180.0 / PI);
	degrees = fmod((degrees + 360.0), 360.0);
	return degrees;
}

int	direction(t_game *game)
{
	int	angle;

	angle = get_rotation_angle(game);
	if (angle <= 45 || angle > 315)
		return (0);
	else if (angle >= 135 && angle < 225)
		return (1);
	else if (angle > 45 && angle < 135)
		return (2);
	return (3);
}


void	destroy_block(t_game *game)
{
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == 'D' && direction(game) == 2)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = '0';
	else if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] == 'D' && direction(game) == 3)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = '0';
	else if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == 'D' && direction(game) == 0)
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = '0';
	else if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] == 'D' && direction(game) == 1)
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = '0';
	

}

void	place_block(t_game *game)
{
	if (game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] == '0' && direction(game) == 2)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y + 1] = 'D';
	else if ((int)game->rc.pos.y - 1 != 0 && game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] == '0' && direction(game) == 3)
		game->map.map[(int)game->rc.pos.x][(int)game->rc.pos.y - 1] = 'D';
	else if (game->map.map[(int)game->rc.pos.x + 1] && game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] == '0' && direction(game) == 0)
		game->map.map[(int)game->rc.pos.x + 1][(int)game->rc.pos.y] = 'D';
	else if ((int)game->rc.pos.x != 0 && game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] == '0' && direction(game) == 1)
		game->map.map[(int)game->rc.pos.x - 1][(int)game->rc.pos.y] = 'D';
}