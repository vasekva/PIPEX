/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:36:32 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/03 19:36:33 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <errno.h>

#ifndef BUFFER_SIZE
	# define	BUFFER_SIZE 32
#endif

#include "libft.h"

void	arr_free(char **array);
int		get_next_line(int fd, char **line);

#endif