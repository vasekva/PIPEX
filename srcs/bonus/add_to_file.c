/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 02:15:45 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/05 02:15:48 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	read_line(char **argv, int *fd)
{
	char	*line;

	while (get_next_line(&line))
	{
		if (!ft_strncmp_old(line, argv[2], ft_strlen(argv[2])))
			exit(0);
		write(fd[1], line, ft_strlen(line));
	}
}

void	run_processes(int *fd, int pid, char **argv)
{
	if (pid == 0)
	{
		close(fd[0]);
		read_line(argv, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		wait(NULL);
	}
}

void	add_to_file(t_file *s_file, int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;

	s_file->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (s_file->fd_out < 0)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	if (pipe(fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	run_processes(fd, pid, argv);
}
