/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:42 by jcario            #+#    #+#             */
/*   Updated: 2024/01/05 14:23:06 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main()
{
	// mlx_t		*mlx;
	// mlx_image_t*	img;
	
	// mlx = mlx_init(WIDTH, HEIGHT, "dinozaur", TRUE);
	// img = mlx_new_image(mlx, 256, 128);
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	// mlx_image_to_window(mlx, img, 0, 0);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// return (0);
	t_map	map;
	int		i;

	i = -1;
	if (!init_map("maps/map.txt", &map))
	{
		printf("invalid map");
		return (1);
	}
	while (map.map[++i])
		printf("%s\n", map.map[i]);
	return (0);
}