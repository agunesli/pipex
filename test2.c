#include <stdio.h>
#include "pipex.h"

char	**found_path(char **env)
{
	int 	i;
	char	*path;
	char	*tmp;

	while (env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' 
				&& env[i][3] == 'H' && env[i][4] == '=' && env[i][5] == '/') 
		{
			path = ft_strdup(env[i]);
//			printf("%s\n\n",path);
			break ;
		}
		i++;
	}
	tmp = path;
	path = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
	free(tmp);
	bin = ft_split(path, ':');
	return (bin);

}

int main(int ac, char **ag, char **env)
{
	(void)ac;
	(void)ag;
	int 	i = 0;
	char	*path;
	char	**bin;
	char	*tmp;


	path = NULL;
/*	i = 0;
	while (bin[i] != NULL)
	{
		printf("%s\n", bin[i]);
		i++;
	}*/
	return (0);
}

