#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	arr_free(char **array)
{
	int	ind;

	ind = 0;
	if (array != NULL)
	{
		while (array[ind])
		{
			if (array[ind] != NULL)
			{
				free(array[ind]);
				array[ind] = NULL;
			}
			ind++;
		}
		free(array);
		array = NULL;
	}
}

void	error(char *str)
{
	perror(str);
	exit(errno);
}

int	execute(char *argv, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	cmd = ft_split(argv, ' ');
	while (ft_strncmp_old(envp[++i], "PATH", 4));
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], ft_strjoin("/", cmd[0], -1), 1);
		if (access(path, F_OK) == 0)
		{
			arr_free(paths);
			if (execve(path, cmd, envp) == -1)
				return (-1);
			else
				return (1);
		}
	}
	arr_free(paths);
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		file_fd;
	int		status;
	pid_t	pid;

	file_fd = 0;
	pid = 0;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("pipe create error");
		pid = fork();
		if (pid == -1)
			error("fork: ");
		if (pid == 0)
		{
			file_fd = open(argv[1], O_RDONLY, 0777);
			if (file_fd == -1)
				error("open file failed");
			dup2(fd[1], 1);
			dup2(file_fd, 0);
			close(fd[0]);
			if (execute(argv[2], envp) == -1)
			{
//				perror("Error");
				write(2, "command not found\n", 18);
				exit(ENOENT);
			}
		}
		waitpid(pid, &status, 0);
		if (status < 0)
			error("child process error");
		if (pid > 0)
		{
			file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (file_fd == -1)
				error("open file failed");
			dup2(fd[0], 0);
			dup2(file_fd, 1);
			close(fd[1]);
			if (execute(argv[3], envp) == -1)
			{
//				perror("Error");
				write(2, "command not found\n", 18);
				exit(ENOENT);
			}
		}
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> file2\n", 1);
	}
	return (1);
}



//
//void	error(void)
//{
//	perror("\033[31mError");
//	exit(EXIT_FAILURE);
//}
//
//void	execute(char *argv, char **envp)
//{
//	int		i;
//	char	**cmd;
//	char	*path;
//	char	**paths;
//
//	i = -1;
//	path = NULL;
//	cmd = ft_split(argv, ' ');
//	while (envp[++i])
//	{
//		if (!ft_strncmp_old(envp[i], "PATH", 4))
//		{
//			paths = ft_split(envp[i] + 5, ':');
//			break ;
//		}
//	}
//	i = -1;
//	while (paths[++i])
//	{
//		path = ft_strjoin(paths[i], ft_strjoin("/", cmd[0], -1), 1);
//		if (access(path, F_OK) == 0)
//		{
//			arr_free(paths);
//			execve(path, cmd, envp);
//		}
//	}
//}
//
//void	child_process(char **argv, char **envp, int *fd)
//{
//	int		filein;
//
//	filein = open(argv[1], O_RDONLY, 0777);
//	if (filein == -1)
//		error();
//	dup2(fd[1], STDOUT_FILENO);
//	dup2(filein, STDIN_FILENO);
//	close(fd[0]);
//	execute(argv[2], envp);
//}
//
//void	parent_process(char **argv, char **envp, int *fd)
//{
//	int		fileout;
//
//	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
//	if (fileout == -1)
//		error();
//	dup2(fd[0], STDIN_FILENO);
//	dup2(fileout, STDOUT_FILENO);
//	close(fd[1]);
//	execute(argv[3], envp);
//}
//
//int	main(int argc, char **argv, char **envp)
//{
//	int	fd[2];
//	int	pid1;
//
//	if (argc == 5)
//	{
//		if (pipe(fd) == -1)
//			error();
//		pid1 = fork();
//		if (pid1 == -1)
//			error();
//		if (pid1 == 0)
//			child_process(argv, envp, fd);
//		waitpid(pid1, NULL, 0);
//		parent_process(argv, envp, fd);
//		close(fd[0]);
//		close(fd[1]);
//	}
//	else
//	{
//		printf("\033[31mError: Bad arguments\n\e[0m");
//		printf("Ex: ./pipex <file1> <cmd1> <cmd2> file2\n");
//	}
//	return (0);
//}
