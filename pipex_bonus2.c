/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:59:27 by agunesli          #+#    #+#             */
/*   Updated: 2022/04/06 23:05:48 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int **fds, int nb_process, int i)
{
	int	j;

	j = 0;
	while (j < nb_process)
	{
		if (j != i || i == 0)
		{
			if (close(fds[j][0]) == -1)
				merror("Error with close\n");
		}
		if (j != i + 1 || i == nb_process - 1)
		{
			if (close(fds[j][1]) == -1)
				merror("Error with close\n");
		}
		j++;
	}
}

t_cmd	create_t_cmd(t_donnee *don, int i)
{
	t_cmd	sc;

	if (don->here_doc)
	{
		sc.cmd_arg = ft_split(don->argv[i + 3], ' ');
		sc.path = correct_path(don->argv[i + 3], don->env, sc.cmd_arg);
	}
	else
	{
		sc.cmd_arg = ft_split(don->argv[i + 2], ' ');
		sc.path = correct_path(don->argv[i + 2], don->env, sc.cmd_arg);
	}
	return (sc);
}

void	not_execve(t_donnee *don, int *childs, t_cmd *scmd, int i)
{
	free_all(scmd->cmd_arg);
	free(scmd->path);
	free(childs);
	if (close(don->fds[i][0]) == -1)
		merror("Error with close\n");
	if (close(don->fds[i + 1][1]) == -1)
		merror("Error with close\n");
	free_all_int(don->fds, don->nb_process);
	merror("Error with execve\n");
}

int	*create_childs(t_donnee *don)
{
	int		*childs;
	int		i;
	t_cmd	scmd;

	childs = (int *)malloc(sizeof(int) * don->nb_process);
	if (!childs)
		merror("Error with malloc childs\n");
	i = -1;
	while (++i < don->nb_process)
	{
		childs[i] = fork();
		if (childs[i] == -1)
			merror("Error with fork child\n");
		if (childs[i] == 0)
		{
			close_fds(don->fds, don->nb_process, i);
			ft_dup2(don->fds, i, don->nb_process, don->argv);
			scmd = create_t_cmd(don, i);
			if (execve(scmd.path, scmd.cmd_arg, don->env) == -1)
				not_execve(don, childs, &scmd, i);
		}
		if (don->here_doc && i == 0)
			waitpid(childs[0], NULL, 0);
	}
	return (childs);
}

t_don	create_struct(int **fds, int nb_process, char **argv, char **env)
{
	t_donnee	don;

	don.fds = fds;
	don.nb_process = nb_process;
	if (!ft_strncmp("here_doc", argv[1], 8))
		don.here_doc = 1;
	else
		don.here_doc = 0;
	don.argv = argv;
	don.env = env;
	return (don);
}
