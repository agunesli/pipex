
#include "pipex.h"

void	close_file(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}


int	main(int ac, char **ag)
{
	int	fd_int;
	int	fd_out;

	if (ac != 5)
	{
		ft_putstr_fd("Error nbr elem", 1);
		return (0);
	}
	if (!check_ag(ag))
		return (0);

	close_file(fd_int, fd_out);

}
