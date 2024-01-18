/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:13:16 by jcario            #+#    #+#             */
/*   Updated: 2024/01/18 12:29:54 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*extract_texture(char *line)
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
