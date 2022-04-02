/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:59:27 by agunesli          #+#    #+#             */
/*   Updated: 2022/04/01 15:04:46 by agunesli         ###   ########.fr       */
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

t_cmd	create_t_cmd(t_donnee *donnee, int i)
{
	t_cmd	scmd;

	if (donnee->here_doc)
	{
		scmd.cmd_arg = ft_split(donnee->argv[i + 3], ' ');
		scmd.path = correct_path(donnee->argv[i + 3], donnee->env);
	}
	else
	{
		scmd.cmd_arg = ft_split(donnee->argv[i + 2], ' ');
		scmd.path = correct_path(donnee->argv[i + 2], donnee->env);
	}
	return (scmd);
}

void	not_execve(t_donnee *donnee, int *childs, t_cmd *scmd, int i)
{
	free_all(scmd->cmd_arg);
	free(scmd->path);
	free(childs);
	if (close(donnee->fds[i][0]) == -1)
		merror("Error with close\n");
	if (close(donnee->fds[i + 1][1]) == -1)
		merror("Error with close\n");
	free_all_int(donnee->fds, donnee->nb_process);
	merror("Error with execve\n");
}

int	*create_childs(t_donnee *donnee)
{
	int		*childs;
	int		i;
	t_cmd	scmd;

	childs = (int *)malloc(sizeof(int) * donnee->nb_process);
	if (!childs)
		merror("Error with malloc childs\n");
	i = 0;
	while (i < donnee->nb_process)
	{
		childs[i] = fork();
		if (childs[i] == -1)
			merror("Error with fork child\n");
		if (donnee->here_doc)
			waitpid(childs[0], NULL, 0);
		if (childs[i] == 0)
		{
			close_fds(donnee->fds, donnee->nb_process, i);
			ft_dup2(donnee->fds, i, donnee->nb_process, donnee->argv);
			scmd = create_t_cmd(donnee, i);
			if (execve(scmd.path, scmd.cmd_arg, donnee->env) == -1)
				not_execve(donnee, childs, &scmd, i);
		}
		i++;
	}
	return (childs);
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
