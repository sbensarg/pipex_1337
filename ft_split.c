/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:59:44 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/14 16:06:47 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	coun(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	len_mot(char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char	**ft_tofree(char *tab[], int j)
{
	while (--j > 0)
		free(tab[j]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(*tab) * (coun((char *)s, c) + 1));
	while (s[i] != '\0' && j < coun((char *)s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		tab[j] = malloc(len_mot((char *)s, c, i) + 1);
		if (!tab[j])
			return (ft_tofree(tab, j));
		while (s[i] != c && s[i] != '\0')
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
