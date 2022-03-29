/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:27:19 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/29 19:10:36 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define BUFFER_SIZE 42

int	ft_nl(char	*buf)
{
	int	len;

	len = 0;
	if (buf == NULL)
		return (0);
	while (buf[len])
	{
		if (buf[len] == '\n')
			return (len + 1);
		len++;
	}
	return (0);
}

char	*ft_buffer_add(char *buffer, char *buf)
{
	char	*tmp;

	tmp = buffer;
	buffer = ft_strjoin(tmp, buf);
	free(tmp);
	return (buffer);
}

char	*ft_buffer_rm(char *buffer, int len)
{
	char	*tmp;

	tmp = buffer;
	buffer = ft_substr_end(tmp, len, ft_strlen(tmp));
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	int			len_nb[2];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	len_nb[0] = ft_nl(buffer);
	if (len_nb[0])
	{
		tmp = ft_substr_end(buffer, 0, len_nb[0]);
		buffer = ft_buffer_rm(buffer, len_nb[0]);
		return (tmp);
	}
	len_nb[1] = read(fd, buf, BUFFER_SIZE);
	if (len_nb[1] > 0)
		buf[len_nb[1]] = '\0';
	if (0 < len_nb[1] && len_nb[1] <= BUFFER_SIZE)
	{
		buffer = ft_buffer_add(buffer, buf);
		return (get_next_line(fd));
	}
	tmp = buffer;
	buffer = NULL;
	return (tmp);
}
