/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:54:35 by jcario            #+#    #+#             */
/*   Updated: 2024/01/25 13:59:45 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_args(int ac, char **av, t_game *game)
{
	if (ac != 2 || !valid_ext(av[1]))
	{
		if (ac == 3 && !ft_strcmp(av[2], "drunk_mode") && valid_ext(av[1]))
			game->drunk = 1;
		else
		{
			ft_putstr_fd("Error : No map detected.\n", 2);
			return (0);
		}
	}
	return (1);
}
