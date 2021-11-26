/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:37:44 by nenvoy            #+#    #+#             */
/*   Updated: 2021/11/26 15:37:44 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
}

static void	*multi_free(char **paths, char *cmd, char *path)
{
	char	*tmp;

	ft_free(paths);
	free(path);
	tmp = cmd;
	free(tmp);
	return (cmd);
}

static int	find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (i);
}

char	*check_path(char *command, char **envp)
{
	char	**paths;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	paths = ft_split(envp[find_path(envp)] + 5, ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(path, command);
		if (access(cmd, F_OK) == 0)
			return (multi_free(paths, cmd, path));
		else
		{
			free(path);
			free(cmd);
			i++;
		}
	}
	ft_free(paths);
	return (0);
}
