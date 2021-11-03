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

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execute(argv, envp) == -1)
		{
			write(2, "Error: command not found\n", 25);
			exit(127);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(0, &line))
		{
			if (ft_strncmp_old(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp_old(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fileout == -1)
			{
				write(2, "Error: file open error\n", 23);
				exit(1);
			}
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fileout == -1)
			{
				write(2, "Error: file open error\n", 23);
				exit(1);
			}
			filein = open(argv[1], O_RDONLY, 0777);
			if (filein == -1)
			{
				write(2, "Error: file open error\n", 23);
				exit(1);
			}
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	else
		write(2, "Error: Program must use more than five arguments\n", 37);
}
