/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:52:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/05 14:28:04 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define WIDTH 512
# define HEIGHT 512

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

typedef struct s_map
{
	char	**map;
} t_map;
int	init_map(char *name, t_map *map);

typedef struct s_coordinates
{
	float	x;
	float	y;
} t_coordinates;

typedef struct s_player
{
	t_coordinates coords;
} t_player;


#endif