/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:28:44 by ael-bako          #+#    #+#             */
/*   Updated: 2022/11/30 16:30:44 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	**freetab(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	return (0);
}

static int	world_len(char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	**fill_arr(int words, char *s, char c, char **arr)
{
	int	k;
	int	i;
	int	j;

	i = 0;
	k = 0;
	while (k < words)
	{
		j = 0;
		arr[k] = malloc(world_len(s, c, i) + 2);
		if (!arr[k])
			return (freetab(arr));
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			arr[k][j++] = s[i++];
		arr[k][j++] = '/';
		arr[k++][j] = '\0';
	}
	arr[k] = 0;
	return (arr);
}

static int	word_count(char *s, char c)
{
	int	i;
	int	count;

	if (!s || !s[0])
		return (0);
	i = -1;
	count = 0;
	while (s[++i])
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count++;
	return (count);
}

char	**ft_splitpath(char *s, char c)
{
	char	**arr;
	int		words;

	if (!s || !s[0])
		return (NULL);
	words = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = fill_arr(words, s, c, arr);
	return (arr);
}
