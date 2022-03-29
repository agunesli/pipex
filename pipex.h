/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:10:17 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/29 20:18:11 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

// utiles
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		free_all(char **bin);
void		merror(char *str);
int			open_file(char *file, int i);
char		*correct_path(char *cmd, char **env);
void		free_all_int(int **bin, int nb_process);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//Structure for bonus
typedef struct s_donnee
{
	int		**fds;
	int		nb_process;
	int		here_doc;
	char	**argv;
	char	**env;
}	t_donnee;

typedef struct s_cmd
{
	char	**cmd_arg;
	char	*path;
}	t_cmd;

// Function bonus
t_donnee	create_struct(int **fds, int nb_process, char **argv, char **env);
int			*create_childs(t_donnee *donnee);
void		ft_dup2(int **fds, int i, int nb_process, char **argv);

//Get_next_line
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_substr_end(char const *s, unsigned int start, size_t end);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
#endif
