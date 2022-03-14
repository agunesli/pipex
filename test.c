#include "pipex.h"

int *swap_fd(int fd[2], char *file_in, char *file_out)
{
	int	fdin;
	int	fdout;
	int f1;
	int f2;

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
	dup2(fdin, fd[0]);
	dup2(fdout, fd[1]);
	close(fdin);
	close(fdout);
//	fd[0] = fdin;
//	fd[1] = fdout;
	return (fd);
}
