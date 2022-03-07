#include "pipex.h"
#include <stdio.h>

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	/*if (argc != 5)
	{
		printf("nb d'arg no correct\n");
		return (0);
	}*/

	int	id1;
	int	id2;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("Error with pipe\n");
		return (0);
	}
	id1 = fork();
	if (id1 == -1)
	{
		printf("Error with fork\n");
		return (0);
	}
	id2 = fork();
	if (id2 == -1)
	{
		printf("Error with fork\n");
		return (0);
	}
	/////////////////////////////////////////
	wait(NULL);
	if (id1 == 0)
	{
		execve
	}
	else
	{
		wait(NULL);

	}

	/*
	if (id1 == 0)
	{
		if (id2 == 0)
			printf ("We are in y\n");
		else
			printf ("We are in x\n");
	}
	else
	{
		if (id2 == 0)
			printf ("We are in z\n");
		else 
			printf ("We are in main\n");

	}*/
//	printf("id = %d\n",id1);
//	if (id1 != 0 && id2 != 0)
//	{
//		wait(NULL);
		//printf("id = %d\n",id2);
//	}
	return (0);
}
