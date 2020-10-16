/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:01:37 by mandarin          #+#    #+#             */
/*   Updated: 2020/10/11 19:42:33 by abarbie          ###   ########.fr       */
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

static int in_set(char c, char *set)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

static char	**arralloc(char const *s, char *set)
{
	int words;
	int added;

	if (!s)
		return (NULL);
	words = 0;
	added = 0;
	while (s && *s)
	{
		if (in_set(*s, set))
		{
			words++;
			added = 0;
		}
		else if (!added)
		{
			words++;
			added = 1;
		}
		s++;
	}
	return ((char **)malloc((words + 1) * sizeof(char *)));
}

char		**ft_splitset(char const *s, char *set)
{
	char	**out;
	char	**word_pt;
	size_t	start;
	size_t	end;

	if (!(out = arralloc(s, set)))
		return (NULL);
	word_pt = out;
	start = 0;
	end = 0;
	while (s[start])
	{
		if (in_set(s[start], set))
			end++;
		else
			while (s[end] && !in_set(s[end], set))
				end++;
		if (start < end)
			if (!(*word_pt++ = ft_substr(s, (unsigned int)start, end - start)))
				return (free_arr(out));
		start = end;
	}
	*word_pt = NULL;
	return (out);
}
