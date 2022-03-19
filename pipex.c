#include "pipex.h"
#include <stdio.h>

// A faire 
// regarder la fonction exit
// faire les errors de close 


//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
int main(int argc, char **argv, char **env)
{
/*	(void)argc;
	(void)argv;
	(void)env;*/

	if (argc != 5)
		merror("nb d'arg no correct\n");
	////////////////////////////////////////

	int	child1;
	int	child2;
	int	fd[2];
	int fdin;
	int fdout;
	char	*path;
	char	**cmd_arg;

	fdin = open_file(argv[1], 1);
	fdout = open_file(argv[4], 2);
/*	if (fdin == -1 || fdout == -1)
		return (0);*/
	if (pipe(fd) == -1)
		merror("Error with pipe\n");
	child1 = fork();
	////////////////////////////////////////
	
	if (child1 == -1)
		merror("Error with fork child1\n");
	if (child1 == 0)
	{
		if (close(fd[0]) == -1)
				merror("Error with close\n");
		if (dup2(fdin, STDIN_FILENO) == -1)
			merror("Error with dup2\n");
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
		cmd_arg = ft_split(argv[2], ' ');
		if (cmd_arg == NULL)
			merror("Error with split\n");
		path = correct_path(argv[2], env);
	/*	if (!path)
			return (0);*/
		if (execve(path, cmd_arg, env) == -1)
		{
			free_all(cmd_arg);
			if (close(fd[1]) == -1)
				merror("Error with close\n");
			merror("Error with execve\n");
		}
	}
	////////////////////////////////////////
	
	child2 = fork();
	if (child2 == -1)
		merror("Error with fork child2\n");
	if (child2 == 0)
	{
		if (close(fd[1]) == -1)
			merror("Error with close\n");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			merror("Error with dup2\n");
		if (dup2(fdout, STDOUT_FILENO) == -1)
			merror("Error with dup2\n");
		cmd_arg = ft_split(argv[3], ' ');
		if (cmd_arg == NULL)
			merror("Error with split\n");
		path = correct_path(argv[3], env);
	/*	if (!path)
			return (0);*/
		if (execve(path, cmd_arg, env) == -1)
		{
			free_all(cmd_arg);
			if (close(fd[0]) == -1)
				merror("Error with close\n");
			merror("Error with execve\n");
		}
	}
	////////////////////////////////////////
	
	close(fd[1]);
	close(fd[0]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);
}
