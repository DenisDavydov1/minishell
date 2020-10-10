/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:01:37 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 18:01:37 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_arr(char **arr)
{
	unsigned int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**arralloc(char const *s, char c)
{
	size_t words;

	if (!s)
		return (NULL);
	words = 0;
	while (s && *s)
	{
		if (*s != c)
		{
			words++;
			s = ft_strchr((const char *)s, c);
		}
		else
			s++;
	}
	return ((char **)malloc((words + 1) * sizeof(char *)));
}

char		**ft_split(char const *s, char c)
{
	char	**out;
	char	**word_pt;
	size_t	start;
	size_t	end;

	if (!(out = arralloc(s, c)))
		return (NULL);
	word_pt = out;
	start = 0;
	end = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c && ++start)
			end++;
		while (s[end] && s[end] != c)
			end++;
		if (start < end)
			if (!(*word_pt++ = ft_substr(s, (unsigned int)start, end - start)))
				return (free_arr(out));
		start = end;
	}
	*word_pt = NULL;
	return (out);
}
