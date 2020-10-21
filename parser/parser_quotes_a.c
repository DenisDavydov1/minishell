/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:43:59 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:36 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pq_add_quote(char *out, char *res)
{
	char *tmp;

	tmp = e_strjoin(out, res);
	free(res);
	free(out);
	return (tmp);
}

static char	*pq_add_slash(char *out, char *s, int *i)
{
	char *tmp;
	char *res;

	if (s[*i + 1] == '\'' || s[*i + 1] == '\"' || s[*i + 1] == '\\')
	{
		res = (char *)e_calloc(2, sizeof(char));
		*res = s[*i + 1];
		tmp = e_strjoin(out, res);
		free(res);
		free(out);
		(*i)++;
	}
	else
		tmp = out;
	return (tmp);
}

static char	*parse_double_quote(char *s, int *i, t_ms *ms)
{
	int		start;
	char	*res;
	char	*tmp;
	char	*out;

	start = ++(*i);
	out = e_strdup("");
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$')
			out = pq_add_var(out, s, i, ms);
		else if (s[*i] == '\\')
			out = pq_add_slash(out, s, i);
		else
			out = pq_add_char(out, s, i);
		(*i)++;
	}
	return (out);
}

static char	*parse_quotes(char *s, t_ms *ms)
{
	int		i;
	char	*out;
	char	*tmp;
	char	*res;

	out = e_strdup("");
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
			out = pq_add_quote(out, parse_single_quote(s, &i));
		else if (s[i] == '$')
			out = pq_add_var(out, s, &i, ms);
		else if (s[i] == '\"')
			out = pq_add_quote(out, parse_double_quote(s, &i, ms));
		else if (i == 0 && s[0] == '~' && \
			(!s[1] || s[1] == ' ' || s[1] == '/'))
			out = e_strdup(find_in_env(ms, "HOME"));
		else if (s[i] == '\\')
			out = pq_add_slash(out, s, &i);
		else
			out = pq_add_char(out, s, &i);
	}
	free(s);
	return (out);
}

void		tcmd_parse_quotes(t_ms *ms)
{
	t_cmd	*p;
	char	*pt;
	int		i;

	p = ms->cmd;
	p->name = p->name ? parse_quotes(p->name, ms) : p->name;
	i = -1;
	while (p->flag && p->flag[++i])
		p->flag[i] = parse_quotes(p->flag[i], ms);
	i = -1;
	while (p->arg && p->arg[++i])
		p->arg[i] = parse_quotes(p->arg[i], ms);
	p->file = p->file ? parse_quotes(p->file, ms) : p->file;
}
