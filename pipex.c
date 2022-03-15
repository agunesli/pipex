#include "pipex.h"
#include <stdio.h>

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
int main(int argc, char **argv, char **env)
{
	(vochild)argc;
	(vochild)argv;
	(vochild)env;

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
	int	child1;
	int	child2;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("Error with pipe\n");
		return (0);
	}
	child1 = fork();
	if (child1 == -1)
	{
		printf("Error with fork child1\n");
		return (0);
	}
	/////////////////////////////////////////
//	wait(NULL);
	if (child1 == 0)
	{
		dup2(fd[1], fdin);
		close(fd[0]);
		execve(/*cm1*/);
		close(fd[1]);
	}
	child2 = fork();
	if (child2 == -1)
	{
		printf("Error with fork child2\n");
		return (0);
	}
	if (child1 == 0)
	{
		dup2(fd[0], fdout);
		close(fd[1]);
		execve(/*cmd2*/);
		close(fd[0]);
	}
	close(fd[1]);
	close(fd[0]);
	waitpchild(child1, NULL, 0);
	waitpchild(child2, NULL, 0);
	return (0);
}
