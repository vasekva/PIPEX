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

static void	lst_cmd(char **argv, char **envp, int *fd)
{
	int	file_fd;

	file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(file_fd, 1);
	close(file_fd);
	close(fd[1]);
	if (execute(argv[3], envp) == -1)
	{
		write(2, "Error: command not found\n", 25);
		exit(127);
	}
}

static void	fst_cmd(char **argv, char **envp, int *fd)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY, 0777);
	if (file_fd == -1)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(file_fd, 0);
	close(file_fd);
	close(fd[0]);
	if (execute(argv[2], envp) == -1)
	{
		write(2, "Error: command not found\n", 25);
		exit(127);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	pid = 0;
	status = 0;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			fst_cmd(argv, envp, fd);
		if (pid > 0)
			lst_cmd(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else
		write(2, "Error: Program uses only 5 arguments\n", 27);
	return (1);
}
