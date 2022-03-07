#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

//Structure
typedef struct s_pip
{
	int		fd_int;
	int		fd_out;
	char	**cmd;
}	t_pip;

void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	**create_cmd(char **ag);

#endif
