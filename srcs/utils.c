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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				def;
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	def = ft_strlen(s1) - ft_strlen(s2);
	if (def < 0)
		return (-1);
	if (def > 0)
		return (1);
	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	while (n-- != 0 && (*p_s1 || *p_s2))
	{
		if (*p_s1 < *p_s2)
			return (-1);
		if (*p_s1 > *p_s2)
			return (1);
		p_s1++;
		p_s2++;
	}
	return (0);
}

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
			execve(path, cmds, envp);
			return (-1);
		}
		free(path);
	}
	arr_free(paths);
	return (-1);
}

int	execute(char *arg, char **envp)
{
	char	**cmds;
	char	**paths;
	int		ret;
	int		i;

	cmds = ft_split(arg, ' ');
	if (!cmds)
		exit(1);
	i = -1;
	ret = 0;
	while (envp[++i])
	{
		if (!ft_strncmp_old(envp[i], "PATH", 4))
			break ;
	}
	paths = ft_split(envp[i] + 5, ':');
	ret = exec_cmd(paths, cmds, envp);
	arr_free(cmds);
	return (ret);
}

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
