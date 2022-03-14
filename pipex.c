#include "pipex.h"
#include <stdio.h>

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
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
	////////////////////////////////////////
	// execve in child process ////////////
	// ////////////////////////////////////
	int	err;
	err = execve(/*  */);
	if (err == -1)
	{
		printf("Error with execve\n");
		return (0);
	}
	////////////////////////////////////////
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
	/////////////////////////////////////////
//	wait(NULL);
	if (id1 == 0)
	{
		dup2(fd[1], fdin);
		close(fd[1]);
		close(fd[0]);
		execve(/*cm1*/);
//		write 
//		close(fdin);
	}

	id2 = fork();
	if (id2 == -1)
	{
		printf("Error with fork\n");
		return (0);
	}
	if (id1 == 0)
	{
		dup2(fd[0], fdout);
		close(fd[1]);
		close(fd[0]);
		execve(/*cmd2*/);
//		write 
// 		close(fdout);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);


	else
	{
		close(fd[1]);
		wait(NULL);
		read
		close(fd[0]);

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
