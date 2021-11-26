/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:37:44 by nenvoy            #+#    #+#             */
/*   Updated: 2021/11/26 15:37:44 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*STDIN_FILENO    0       Standard input.  */
/*STDOUT_FILENO   1       Standard output.  */
/*STDERR_FILENO   2       Standard error output.  */

void	error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

static void	ft_child(int *fd, char **argv, char **envp)
{
	int		file;
	char	**cmd;

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error("open file1");
	if ((dup2(fd[1], STDOUT_FILENO)) == -1)
		error("dup2 fd[1]");
	if ((dup2(file, STDIN_FILENO)) == -1)
		error("dup2 file 1");
	close(fd[0]);
	cmd = ft_split(argv[2], ' ');
	if (execve(check_path(cmd[0], envp), cmd, envp) == -1)
		error("cmd1 not found");
}

static void	ft_parent(int *fd, char **argv, char **envp)
{
	int		file;
	char	**cmd;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error("open file2");
	if ((dup2(fd[0], STDIN_FILENO)) == -1)
		error("dup2 fd[0]");
	if ((dup2(file, STDOUT_FILENO)) == -1)
		error("dup2 file2");
	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	if (execve(check_path(cmd[0], envp), cmd, envp) == -1)
		error("cmd2 not found");
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("pipe");
		pid = fork();
		if (pid == -1)
			error("fork");
		if (pid == 0)
			ft_child(fd, argv, envp);
		wait(NULL);
		ft_parent(fd, argv, envp);
	}
	else
		ft_putstr_fd("erro! use: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (0);
}
