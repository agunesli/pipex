/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:08:23 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/20 16:08:38 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
char	**found_path(char **env)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**bin;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (!ft_strncmp("PATH=/", env[i], 6))
		{
			path = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	if (path == NULL)
		merror("error with env\n");
	tmp = path;
	path = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
	free(tmp);
	bin = ft_split(path, ':');
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

char	*found_cmd(char *cmd)
{
	char	**cmd_ag;
	char	*cmdd;

	cmd_ag = ft_split(cmd, ' ');
	cmdd = ft_strjoin("/", cmd_ag[0]);
	free_all(cmd_ag);
	if (cmdd == NULL)
		merror("Error with split\n");
	return (cmdd);
}

char	*correct_path(char *cmd, char **env)
{
	char	**bin;
	char	*tmp;
	int		i;
	int		len;
	char	*cmdd;

	i = 0;
	bin = found_path(env);
	len = len_bin(bin);
	cmdd = found_cmd(cmd);
	tmp = ft_strjoin(bin[0], cmdd);
	while (++i < len && access(tmp, F_OK) != 0)
	{
		free(tmp);
		tmp = ft_strjoin(bin[i], cmdd);
	}
	free(cmdd);
	free_all(bin);
	if (i == len)
	{
		merror("Command no found\n");
		return (NULL);
	}
	else
		return (tmp);
}
