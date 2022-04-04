/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:08:59 by agunesli          #+#    #+#             */
/*   Updated: 2022/04/04 10:34:29 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_all_int(int **bin, int nb_process)
{
	int	i;

	i = 0;
	while (i < nb_process)
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
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00777);
		if (fd == -1)
			merror("Error open file out\n");
		return (fd);
	}
	else if (i == 3)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00777);
		if (fd == -1)
			merror("Error open file out\n");
		return (fd);
	}
	return (-1);
}
