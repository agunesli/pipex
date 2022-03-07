#include "pipex.h"

int *swap_fd(int fd[2], char *file_in, char *file_out)
{
	int	fdin;
	int	fdout;

	fdin = open(file_in, O_RDONLY);
	if (fdin == -1)
	{
		printf("Error open file in\n");
		return (NULL);
	}
	fdout = open(file_out, O_RDONLY);
	if (fdout == -1)
	{
		printf("Error open file out\n");
		return (NULL);
	}
	close(fd[0]);
	close(fd[1]);
	fd[0] = fdin;
	fd[1] = fdout;
	return (fd);
}
