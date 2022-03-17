#include "pipex.h"

void	free_all(char   **bin)
{
	int i;

	i = 0;
	while (bin[i])
	{
		free(bin[i]);
		i++;
	}
	free(bin);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int open_file(char *file, int i)
{
	int fd;

	if (i == 1)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr("Error open file in\n");
			return (-1);
		}
		return (fd);
	}
	else if (i == 2)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC);
		if (fd == -1)
		{
			ft_putstr("Error open file out\n");
			return (-1);
		}
		return (fd);
	}
	return (-1);
}
