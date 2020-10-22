/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_common_utils_d.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:21:12 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:29:14 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	charxx_free(char **s)
{
	char **p;

	if (!s)
		return ;
	p = s;
	while (*p)
	{
		free(*p);
		p++;
	}
	free(s);
}

char	**charxx_alloc(int size)
{
	char **out;

	out = NULL;
	if (size > 0)
	{
		out = (char **)e_malloc(sizeof(char *) * (size + 1));
		while (size >= 0)
			out[size--] = NULL;
	}
	return (out);
}

int		charxx_len(char **ss)
{
	int len;

	len = 0;
	while (ss && *ss)
	{
		ss++;
		len++;
	}
	return (len);
}

char	**charxx_insert(char **ss, char *s, int pos)
{
	char	**out;
	int		i;

	if (!ss)
	{
		out = charxx_alloc(2);
		out[0] = e_strdup(s);
		return (out);
	}
	out = charxx_alloc(charxx_len(ss) + 2);
	i = -1;
	while (++i < pos)
		out[i] = e_strdup(ss[i]);
	out[i] = e_strdup(s);
	while (ss && ss[i])
	{
		out[i + 1] = e_strdup(ss[i]);
		i++;
	}
	charxx_free(ss);
	return (out);
}

char	**charxx_delete_one(char **ss, int pos)
{
	char	**out;
	int		i;

	if (!ss)
		return (NULL);
	out = charxx_alloc(charxx_len(ss));
	i = -1;
	while (++i < pos)
		out[i] = e_strdup(ss[i]);
	while (ss && ss[++i])
	{
		out[i - 1] = ss[i];
		i++;
	}
	charxx_free(ss);
	return (out);
}
