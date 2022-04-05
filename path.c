/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:08:23 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/28 21:47:09 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**found_path(char **env, char **cmd_arg)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**bin;

	i = ((path = NULL, -1));
	while (env[++i] != NULL)
	{
		if (!ft_strncmp("PATH=/", env[i], 6))
		{
			path = ft_strdup(env[i]);
			break ;
		}
	}
	if (path == NULL)
	{
		free(path);
		free_all(cmd_arg);
		merror("error with env\n");
	}
	tmp = path;
	path = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
	bin = ((free(tmp), ft_split(path, ':')));
	free(path);
	return (bin);
}

int	len_bin(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
		i++;
	return (i);
}

char	*found_cmd(char *cmd, char **bin, char **cmd_arg)
{
	char	**cmd_ag;
	char	*cmdd;

	cmd_ag = ft_split(cmd, ' ');
	cmdd = ft_strjoin("/", cmd_ag[0]);
	free_all(cmd_ag);
	if (cmdd == NULL)
	{
		free_all(bin);
		free_all(cmd_arg);
		merror("Error with split\n");
	}
	return (cmdd);
}

char	*correct_path(char *cmd, char **env, char **cmd_arg)
{
	char	**bin;
	char	*tmp;
	int		i;
	int		len;
	char	*cmdd;

	bin = ((i = 0, found_path(env, cmd_arg)));
	cmdd = ((len = len_bin(bin), found_cmd(cmd, bin, cmd_arg)));
	tmp = ft_strjoin(bin[0], cmdd);
	while (++i < len && access(tmp, F_OK) != 0)
		tmp = ((free(tmp), ft_strjoin(bin[i], cmdd)));
	free(cmdd);
	free_all(bin);
	if (i == len)
	{
		free_all(cmd_arg);
		free(tmp);
		return (merror("Command no found\n"), NULL);
	}
	else
		return (tmp);
}
