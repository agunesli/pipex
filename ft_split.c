/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:12:58 by agunesli          #+#    #+#             */
/*   Updated: 2021/12/09 19:33:08 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_big_malloc(char const *s, char c)
{
	size_t	i;
	size_t	cpt;
	char	**dst;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i + 1] && i != 0 && s[i] == c && s[i + 1] != c)
			cpt++;
		i++;
	}
	dst = (char **)malloc(sizeof(char *) * (cpt + 2));
	if (!dst)
		return (NULL);
	return (dst);
}

static char	**ft_free_all(char **d, size_t j)
{
	while (j > -1)
	{
		free(d[j]);
		j--;
	}
	free(d);
	return (NULL);
}

size_t	ft_len_word(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**ft_subsplit(char const *s, char **dst, char c)
{
	size_t	len;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (s[i] && i <= ft_strlen(s))
	{
		len = ft_len_word(s + i, c);
		if (len != 0)
		{
			dst[j] = ft_substr(s, i, len);
			if (!dst[j])
				return (ft_free_all(dst, j));
			j++;
			if (len + i == ft_strlen(s))
				len--;
		}
		i += (len + 1);
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	dst = ft_big_malloc(s, c);
	if (!dst)
		return (NULL);
	dst = ft_subsplit(s, dst, c);
	return (dst);
}
