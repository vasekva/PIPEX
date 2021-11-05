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

# include <fcntl.h>
# include <errno.h>

# define	BUFFER_SIZE 32

# include "libft.h"

typedef struct s_file
{
	int		fd_out;
	int		fd_in;
}				t_file;

void	arr_free(char **array);
int		get_next_line(char **line);
int		execute(char *arg, char **envp);
void	add_to_file(t_file *s_file, int argc, char **argv);

#endif