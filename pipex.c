/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:07:27 by agunesli          #+#    #+#             */
/*   Updated: 2022/04/05 23:23:00 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	ft_child1(int *fd, char *file, char *argv, char **env)
{
	char	**cmd_arg;
	char	*path;
	int		fdin;

	fdin = open_file(file, 1);
	if (close(fd[0]) == -1)
		merror("Error with close\n");
	if (dup2(fdin, STDIN_FILENO) == -1)
		merror("Error with dup2\n");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		merror("Error with dup2\n");
	cmd_arg = ft_split(argv, ' ');
	if (cmd_arg == NULL)
		merror("Error with split\n");
	path = correct_path(argv, env);
	if (execve(path, cmd_arg, env) == -1)
	{
		free_all(cmd_arg);
		if (close(fd[1]) == -1)
			merror("Error with close\n");
		merror("Error with execve\n");
	}
}

void	ft_child2(int *fd, char *file, char *argv, char **env)
{
	char	**cmd_arg;
	char	*path;
	int		fdout;

	fdout = open_file(file, 2);
	if (close(fd[1]) == -1)
		merror("Error with close\n");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		merror("Error with dup2\n");
	if (dup2(fdout, STDOUT_FILENO) == -1)
		merror("Error with dup2\n");
	cmd_arg = ft_split(argv, ' ');
	if (cmd_arg == NULL)
		merror("Error with split\n");
	path = correct_path(argv, env);
	if (execve(path, cmd_arg, env) == -1)
	{
		free_all(cmd_arg);
		if (close(fd[0]) == -1)
			merror("Error with close\n");
		merror("Error with execve\n");
	}
}

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
int	main(int argc, char **argv, char **env)
{
	int	child1;
	int	child2;
	int	fd[2];

	if (argc != 5)
		merror("nb d'arg no correct\n");
	if (pipe(fd) == -1)
		merror("Error with pipe\n");
	child1 = fork();
	child2 = fork();
	if (child1 == -1 || child2 == -1)
		merror("Error with fork child\n");
	if (child1 == 0 && child2 != 0)
		ft_child1(fd, argv[1], argv[2], env);
	if (child2 == 0 && child1 != 0)
		ft_child2(fd, argv[4], argv[3], env);
	if (close(fd[1]) == -1 || close(fd[0]) == -1)
		merror("Error with close\n");
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}
