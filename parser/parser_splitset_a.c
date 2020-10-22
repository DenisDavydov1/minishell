/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_splitset_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:47:27 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:38:17 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			is_esc_char(char *s, int *i)
{
	if (s[*i] && s[*i] == '\\' && (s[*i + 1] == '\'' || s[*i + 1] == '\"' || \
		s[*i + 1] == '\\'))
		return (1);
	return (0);
}

int			get_quote_end(char *s, char quote, int *start)
{
	int end;

	end = *start + 1;
	while (s && s[end] && s[end] != quote)
	{
		if (is_esc_char(s, &end))
			end += 2;
		else
			end++;
	}
	if (s[end] == quote)
		return (end);
	else
		return (0);
}

static int	spltst(char *s, int *end, char *set)
{
	if (is_esc_char(s, end))
	{
		(*end) += 2;
		if (s[*end] && !in_set(s[*end], set))
			return (1);
	}
	else if (s[*end] == '\'' || s[*end] == '\"')
	{
		(*end) = get_quote_end(s, s[*end], end) + 1;
		if (s[*end] && !in_set(s[*end], set))
			return (1);
	}
	else if (in_set(s[*end], set))
		(*end)++;
	else
	{
		while (s[*end] && !in_set(s[*end], set) && !is_esc_char(s, end) && \
			s[*end] != '\'' && s[*end] != '\"')
			(*end)++;
		if (s[*end] && !in_set(s[*end], set) && (is_esc_char(s, end) || \
			s[*end] == '\'' || s[*end] == '\"'))
			return (1);
	}
	return (0);
}

char		**free_arr(char **arr)
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

char		**e_splitset(char *s, char *set)
{
	char	**out;
	char	**word_pt;
	int		start;
	int		end;

	if (!s || !(out = arralloc(s, set)))
		return (NULL);
	word_pt = out;
	start = 0;
	end = 0;
	while (s[start])
	{
		if (spltst(s, &end, set))
			continue ;
		if (start < end)
			if (!(*word_pt++ = ft_substr(s, (unsigned int)start, end - start)))
				return (free_arr(out));
		start = end;
	}
	return (out);
}
