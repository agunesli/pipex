/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:07:27 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/28 21:49:42 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int **fds, int nb_process, int i)
{
	int	j;

	j = 0;
	while (j < nb_process)
	{
		if (j != i)
		{
			if (close(fds[j][0]) == -1)
				merror("Error with close\n");
		}
		if (j != i + 1)
		{
			if (close(fds[j][1]) == -1)
				merror("Error with close\n");
		}
		j++;
	}
}

void	start_for_open(char **argv)
{
	char	*line;
	int		fd;

	if (!ft_strncmp("here_doc", argv[1], 8))
	{
		write(1, "pipe heredoc>", 13);
		line = get_next_line(STDIN_FILENO);
		while (ft_strncmp(argv[2], line, ft_strlen(argv[2])))
		{
			write(fds[1], line, ft_strlen(line));
			free(line);
			write(1, "pipe heredoc>", 13);
			line = get_next_line(STDIN_FILENO);
		}
		free(line);
	}
	else
	{
		fd = open_file(argv[1], 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			merror("Error with dup2\n");
	}
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
	}
	if (i == nb_process - 1)
	{
		fd = open_file(argv[nb_process + 2], 2);
		if (dup2(fd, STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
	}
	else
	{
		if (dup2(fds[i + 1][1], STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
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
	fds[i] = NULL;
	return (fds);
}

int	*create_childs(t_donnee donnee)
{
	int		*childs;
	int		i;
	char	**cmd_arg;
	char	*path;

	childs = (int *)malloc(sizeof(int) * nb_process);
	if (!childs)
		merror("Error with malloc childs\n");
	i = 0;
	while (i < donnee.nb_process)
	{
		childs[i] = fork();
		if (childs[i] == -1)
			merror("Error with fork child\n");
		if (childs[i] == 0)
		{
			close_fds(donnee.fds, donnee.nb_process, i);
			ft_dup2(donnee.fds, i, donnee.nb_process, donnee.argv);
			if (donnee.here_doc)
			{
				cmd_arg = ft_split(donnee.argv[i + 3], ' ');
				path = correct_path(donnee.argv[i + 3], donnee.env);
			}
			else
			{
				cmd_arg = ft_split(donnee.argv[i + 2], ' ');
				path = correct_path(donnee.argv[i + 2], donnee.env);
			}
			if (execve(path, cmd_arg, donnee.env) == -1)
			{
				free_all(cmd_arg);
				free(path);
				free(childs);
				if (close(donnee.fds[i][0]) == -1)
					merror("Error with close\n");
				if (close(donnee.fds[i + 1][1]) == -1)
					merror("Error with close\n");
				free_all_int(donnee.fds);
				merror("Error with execve\n");
			}
		}
		i++;
	}
	return (childs);
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
	free_all_int(fds);
	i = 0;
	while (i < nb_process)
	{
		waitpid(childs[i], NULL, 0);
		i++;
	}
	free(childs);
}

t_donnee	create_struct(int **fds, int nb_process, char **argv, char **env)
{
	t_donnee	donnee;

	donnee.fds = fds;
	donnee.nb_process = nb_process;
	if (!ft_strncmp("here_doc", argv[1], 8))
		donnee.here_doc = 1;
	else
		donnee.here_doc = 0;
	donnee.argv = argv;
	donnee.env = env;
	return (donnee);
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

	if (argc < 5)
		merror("nb d'arg no correct\n");
	here_doc = 0;
	if (!ft_strncmp("here_doc", argv[1], 8))
		here_doc = 1;
	if (here_doc)
		nb_process = argc - 4;
	else
		nb_process = argc - 3;
	fds = create_fds(nb_process);
	donnee = create_struct(fds, nb_process, **argv, **env);
	childs = create_childs(donnee);
	parent(fds, childs, nb_process);
	return (0);
}
