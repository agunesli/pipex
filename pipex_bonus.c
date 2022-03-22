/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:07:27 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/22 15:29:21 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int **pipes, int nb_process, int i)
{
	int	j;

	j = 0;
	while (j < nb_process)
	{
		if (j != i)
		{
			if (close(pipes[j][0]) == -1)
				merror("Error with close\n");
		}
		if (j != i + 1)
		{
			if (close(pipes[j][1]) == -1)
				merror("Error with close\n");
		}
	}
}

void	ft_dup2(int **pipes, int i, int nb_process, char **argv)
{
	int	fd;

	if (i == 0)
	{
		fd = open_file(argv[1], 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			merror("Error with dup2\n");
	}
	else
	{
		if (dup2(pipes[i][0], STDIN_FILENO) == -1)
			merror("Error with dup2\n");
	}
	if (i == nb_process - 1)
	{
		fd = open_file(argv[nb_process], 2);
		if (dup2(fd, STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
	}
	else
	{
		if (dup2(pipes[i + 1][1], STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
	}
}

int	**create_pipes(int nb_process)
{
	int	i;
	int	**pipes;

	pipes = (int **)malloc(sizeof(int *) * nb_process);
	if (!pipes)
		merror("Error with malloc pipes\n");
	i = 0;
	while (i < nb_process)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			merror("Error with malloc pipes[i]\n");
		if (pipe(pipes[i]) == -1)
			merror("Error with pipe\n");
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

int	*create_childs(int **pipes, int nb_process, char **argv, char **env)
{
	int		*childs;
	int		i;
	char	**cmd_arg;
	char	*path;

	childs = (int *)malloc(sizeof(int) * nb_process);
	if (!childs)
		merror("Error with malloc childs\n");
	i = 0;
	while (i < nb_process)
	{
		childs[i] = fork();
		if (childs[i] == -1)
			merror("Error with fork child\n");
		if (childs[i] == 0)
		{
			close_pipes(pipes, nb_process, i);
			ft_dup2(pipes, i, nb_process, argv);
			cmd_arg = ft_split(argv[i + 2], ' ');
			path = correct_path(argv[i + 2], env);
			if (execve(path, cmd_arg, env) == -1)
			{
				free_all(cmd_arg);
				free(path);
				free(childs);
				if (close(pipes[i][0]) == -1)
					merror("Error with close\n");
				if (close(pipes[i + 1][1]) == -1)
					merror("Error with close\n");
				free_all_int(pipes);
				merror("Error with execve\n");
			}
		}
		i++;
	}
	return (childs);
}

void	create_parent(int **pipes, int *childs, int nb_process)
{
	int	i;

	i = 0;
	while (i < nb_process)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	free_all_int(pipes);
	free(childs);
	i = 0;
	while (i < nb_process)
	{
		waitpid(childs[i], NULL, 0);
		i++;
	}
}

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
//nb_process => argc - 3 car fdint, fdout, pipex
int	main(int argc, char **argv, char **env)
{
	int	**pipes;
	int	*childs;
	int	i;
	int	nb_process;

	if (argc < 5)
		merror("nb d'arg no correct\n");
	i = 0;
	nb_process = argc -3;
	pipes = create_pipes(nb_process);
	childs = create_childs(pipes, nb_process, argv, env);
	create_parent(pipes, childs, nb_process);
	return (0);
}