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

static int	exec_cmd(char **paths, char **cmds, char **envp)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (paths[++i])
	{
		if (!ft_strncmp_old("/bin/", cmds[0], 5))
			path = ft_strjoin(paths[i], cmds[0] + 4, -1);
		else
			path = ft_strjoin(paths[i], ft_strjoin("/", cmds[0], -1), 1);
		if (access(path, F_OK) == 0)
		{
			arr_free(paths);
			if (execve(path, cmds, envp) == -1)
				return (-1);
			else
				return (1);
		}
	}
	return (-1);
}

static int	execute(char *arg, char **envp)
{
	char	**cmds;
	char	**paths;
	int		i;

	cmds = ft_split(arg, ' ');
	if (!cmds)
		exit(1);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp_old(envp[i], "PATH", 4))
			break ;
	}
	paths = ft_split(envp[i] + 5, ':');
	return (exec_cmd(paths, cmds, envp));
}

static void	main_process(char **argv, char **envp, int *fd)
{
	int	file_fd;

	file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd == -1)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(file_fd, 1);
	close(fd[1]);
	if (execute(argv[3], envp) == -1)
	{
		write(2, "Error: command not found\n", 25);
		exit(127);
	}
}

static void	child_process(char **argv, char **envp, int *fd)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY, 0777);
	if (file_fd == -1)
	{
		write(2, "Error: file open error\n", 23);
		exit(1);
	}
	dup2(fd[1], 1);
	dup2(file_fd, 0);
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
	pid_t	pid;

	pid = 0;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			child_process(argv, envp, fd);
		if (pid > 0)
			main_process(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else
		write(2, "Error: Program uses only 5 arguments\n", 27);
	return (1);
}
