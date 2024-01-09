/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:46 by jcario            #+#    #+#             */
/*   Updated: 2024/01/09 21:35:26 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fill_image(mlx_image_t *image)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		vertical_line(0, HEIGHT / 2, x, image, CEILING);
		x++;
	}
	x = 0;
	while (x < WIDTH)
	{
		vertical_line(HEIGHT / 2, HEIGHT - 1, x, image, FLOOR);
		x++;
	}
}

void	vertical_line(int start_y, int end_y, int x, mlx_image_t *image, uint32_t color)
{
	while (start_y <= end_y)
	{
		mlx_put_pixel(image, x, start_y, color);
		start_y++;
	}
}