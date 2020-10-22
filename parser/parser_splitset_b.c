/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_splitset_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:47:49 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:38:42 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		split_countflags(char **s)
{
	int f;

	f = 0;
	while (*s)
	{
		s = tcmd_skip(s);
		if (*s && is_flag(*s))
			f++;
		else
			return (f);
		s++;
	}
	return (f);
}

int		split_countargs(char **s)
{
	int a;

	a = 0;
	while (*s)
	{
		s = tcmd_skip(s);
		if (*s && !in_set(**s, SET))
			a++;
		else
			return (a);
		s++;
	}
	return (a);
}

char	**arralloc(char *s, char *set)
{
	int words;
	int added;
	int i;

	words = 0;
	added = 1;
	i = -1;
	while (s && s[++i])
	{
		if (in_set(s[i], set) && (words += added ? 1 : 2))
			added = 1;
		else if (is_esc_char(s, &i) && !(added = 0))
			i++;
		else if ((s[i] == '\'' || s[i] == '\"') && !(added = 0))
		{
			if (!(i = get_quote_end(s, s[i], &i)))
				return (NULL);
		}
		else
			added = 0;
		if (!s[i + 1] && !added)
			words++;
	}
	return ((char **)e_calloc(words + 1, sizeof(char *)));
}
