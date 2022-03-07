#include "pipex.h"

char	**create_cmd(char **ag)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 3);
	if (!cmd)
		return (NULL);
	cmd[0] = ag[2];
	cmd[1] = ag[3];
	cmd[3] = '\0';
	return (cmd);
}

