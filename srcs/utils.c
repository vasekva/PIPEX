/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:38:39 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/03 19:38:41 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arr_free(char **array)
{
	int	ind;

	ind = -1;
	if (array != NULL)
	{
		while (array[++ind])
		{
			if (array[ind] != NULL)
			{
				free(array[ind]);
				array[ind] = NULL;
			}
		}
		free(array);
		array = NULL;
	}
}
