#include <stdio.h>
#include "pipex.h"

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
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
				&& env[i][3] == 'H' && env[i][4] == '=' && env[i][5] == '/')
		{
			path = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	if (path == NULL)
	{
		ft_putstr("error with env\n");
		return (NULL);
	}
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

char	*correct_path(char *cmd, char **env)
{
	char	**cmd_ag;
	char	**bin;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	cmd_ag = ft_split(cmd, ' ');
	bin = found_path(env);
	if (bin == NULL)
		return (NULL);
	len = len_bin(bin);
	tmp = ft_strjoin(bin[0], cmd_ag[0]);
	while (++i < len && access(tmp, F_OK) != 0)
	{
		free(tmp);
		tmp = ft_strjoin(bin[i], cmd_ag[0]);
	}
	free_all(bin);
	free_all(cmd_ag);
	if (i == len)
	{
		ft_putstr("Command no found\n");
		return (NULL);
	}
	else
		return (tmp);
}
