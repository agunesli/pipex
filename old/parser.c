#include "pipex.h"

int check_ag(char **ag)
{
	t_pip pip;

	pip.fd_int = open(ag[1], O_RDONLY);
	pip.fd_out = open(ag[4], O_WRONLY);
	if (pip.fd_int == -1 || pip.fd_out == -1)
	{
		ft_putstr_fd("Error with open", 1);
		return (0);
	}
	pip.cmd = create_cmd(ag);



}
