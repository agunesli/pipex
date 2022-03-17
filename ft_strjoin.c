/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:52:11 by agunesli          #+#    #+#             */
/*   Updated: 2022/03/16 15:07:24 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		dst[i] = s2[j];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
