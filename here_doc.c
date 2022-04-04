/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:15:04 by agunesli          #+#    #+#             */
/*   Updated: 2022/04/04 12:21:56 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_heredoc(char *lim)
{
	char	*line;
	int		fd;

	fd = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (fd == -1)
		merror("Error with open .here_doc\n");
	if (write(1, "pipe heredoc>", 13) == -1)
		merror("Error with write pipe heredoc\n");
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(lim, line, ft_strlen(lim)))
	{
		if (write(fd, line, ft_strlen(line)) == -1)
			merror("Error with write in .here_doc\n");
		free(line);
		if (write(1, "pipe heredoc>", 13) == -1)
			merror("Error with write pipe heredoc\n");
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(lim);
	if (close(fd) == -1)
		merror("Error wtih close .here_doc\n");
	fd = open_file(".here_doc", 1);
	return (fd);
}
