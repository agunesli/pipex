/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:59:13 by agunesli          #+#    #+#             */
/*   Updated: 2022/04/04 12:21:18 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_for_open(char **argv)
{
	int		fd;
	char	*lim;

	if (!ft_strncmp("here_doc", argv[1], 8))
	{
		lim = ft_strjoin(argv[2], "\n");
		fd = ft_heredoc(lim);
	}
	else
		fd = open_file(argv[1], 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		merror("Error with dup2\n");
	close(fd);
}

void	ft_dup2(int **fds, int i, int nb_process, char **argv)
{
	int		fd;

	if (i == 0)
		start_for_open(argv);
	else
	{
		if (dup2(fds[i][0], STDIN_FILENO) == -1)
			merror("Error with dup2\n");
		close(fds[i][0]);
	}
	if (i == nb_process - 1)
	{
		if (!ft_strncmp("here_doc", argv[1], 8))
			fd = open_file(argv[nb_process + 3], 3);
		else
			fd = open_file(argv[nb_process + 2], 2);
		if (dup2(fd, STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
		close(fd);
	}
	else
	{
		if (dup2(fds[i + 1][1], STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
		close(fds[i + 1][1]);
	}
}

int	**create_fds(int nb_process)
{
	int	i;
	int	**fds;

	fds = (int **)malloc(sizeof(int *) * nb_process);
	if (!fds)
		merror("Error with malloc fds\n");
	i = 0;
	while (i < nb_process)
	{
		fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!fds[i])
			merror("Error with malloc fds[i]\n");
		if (pipe(fds[i]) == -1)
			merror("Error with pipe\n");
		i++;
	}
	return (fds);
}

void	parent(int **fds, int *childs, int nb_process)
{
	int	i;

	i = 0;
	while (i < nb_process)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	free_all_int(fds, nb_process);
	i = 0;
	while (i < nb_process)
	{
		waitpid(childs[i], NULL, 0);
		i++;
	}
	free(childs);
}

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
//nb_process => argc - 3 car fdint, fdout, pipex
int	main(int argc, char **argv, char **env)
{
	int			**fds;
	int			*childs;
	int			here_doc;
	int			nb_process;
	t_donnee	donnee;

	here_doc = 0;
	if (argc < 5)
		merror("nb d'arg no correct\n");
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc = 1;
	if (here_doc && argc < 6)
		merror("nb d'arg no correct\n");
	if (here_doc)
		nb_process = argc - 4;
	else
		nb_process = argc - 3;
	fds = create_fds(nb_process);
	donnee = create_struct(fds, nb_process, argv, env);
	childs = create_childs(&donnee);
	parent(fds, childs, nb_process);
	return (0);
}
