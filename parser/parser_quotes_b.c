/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:44:02 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:38 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*parse_single_quote(char *s, int *i)
{
	int start;

	start = ++(*i);
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	return (e_substr(s, start, *i - start));
}

char		*pq_add_char(char *out, char *s, int *i)
{
	char *tmp;

	tmp = e_calloc(ft_strlen(out) + 2, sizeof(char));
	ft_strlcat(tmp, out, ft_strlen(out) + 1);
	ft_strlcat(tmp, &s[*i], ft_strlen(out) + 2);
	free(out);
	return (tmp);
}

static char	*parse_dollar_sign(char *s, int *i, t_ms *ms)
{
	int		start;
	char	*name;
	char	*value;

	start = ++(*i);
	if (s[*i] == '?')
		return (e_itoa(ms->ret));
	while (s[*i] && !in_set(s[*i], QUOTES) && !in_set(s[*i], SET) && \
		s[*i] != '$' && s[*i] != '\\')
		(*i)++;
	name = e_substr(s, start, *i - start);
	value = find_in_env(ms, name);
	free(name);
	(*i)--;
	return (value ? e_strdup(value) : e_strdup(""));
}

char		*pq_add_var(char *out, char *s, int *i, t_ms *ms)
{
	char *tmp;
	char *res;

	if (!s[*i + 1] || s[*i + 1] == ' ' || s[*i + 1] == '\'' || \
		s[*i + 1] == '\"' || s[*i + 1] == '$')
		res = e_strdup("$");
	else
		res = parse_dollar_sign(s, i, ms);
	tmp = e_strjoin(out, res);
	free(res);
	free(out);
	return (tmp);
}
