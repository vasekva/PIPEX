/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:57:15 by jberegon          #+#    #+#             */
/*   Updated: 2021/11/03 18:57:19 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

static void	multiple_execute(t_file *s_file, char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		if (execute(cmd, envp) == -1)
		{
			write(2, "Error: command not found\n", 25);
			exit(127);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

static void	open_files(t_file *s_file, int argc, char **argv)
{
	s_file->fd_out = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (s_file->fd_out == -1)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	s_file->fd_in = open(argv[1], O_RDONLY, 0777);
	if (s_file->fd_in == -1)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	dup2(s_file->fd_in, 0);
}

void	run_program(t_file *s_file, int argc, char **argv, char **envp)
{
	int	i;

	i = -1;
	s_file->fd_in = 0;
	s_file->fd_out = 1;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		i = 3;
		add_to_file(s_file, argc, argv);
	}
	else
	{
		i = 2;
		open_files(s_file, argc, argv);
	}
	while (i + 2 < argc)
		multiple_execute(s_file, argv[i++], envp);
	dup2(s_file->fd_out, 1);
	if (execute(argv[argc - 2], envp))
	{
		write(2, "Error: command not found\n", 25);
		exit(127);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_file	s_file;
	int		i;

	if (argc >= 5)
	{
		run_program(&s_file, argc, argv, envp);
	}
	else
		write(2, "Error: Program must use more than five arguments\n", 49);
	return (1);
}
