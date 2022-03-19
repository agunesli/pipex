#include "pipex.h"

void	free_all(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
	{
		free(bin[i]);
		i++;
	}
	free(bin);
}

void	merror(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int i)
{
	int	fd;

	if (i == 1)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			merror("Error open file in\n");
		return (fd);
	}
	else if (i == 2)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 511);
		if (fd == -1)
			merror("Error open file out\n");
		return (fd);
	}
	return (-1);
}
