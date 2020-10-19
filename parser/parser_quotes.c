#include "../minishell.h"

char *parse_dollar_sign(char *s, int *i, t_ms *ms)
{
	int start;
	char *name;
	char *value;

	start = ++(*i);
	while (s[*i] && !in_set(s[*i], QUOTES) && !in_set(s[*i], SET) && s[*i] != '$')
		(*i)++;
	name = e_substr(s, start, *i - start); //mb *i - 1
	value = find_in_env(ms, name);
	free(name);
	return (value ? value : "");
}

char *parse_single_quote(char *s, int *i)
{
	int start;

	start = ++(*i);
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	return (e_substr(s, start, *i - start)); //mb *i - 1
}

char *pq_add_char(char *out, char *s, int *i)
{
	char *tmp;

	tmp = e_calloc(ft_strlen(out) + 2, sizeof(char));
	ft_strlcat(tmp, out, ft_strlen(out) + 1);
	ft_strlcat(tmp, &s[*i], ft_strlen(out) + 2);
	free(out);
	return (tmp);
}

char *pq_add_var(char *out, char *s, int *i, t_ms *ms)
{
	char *tmp;

	tmp = e_strjoin(out, parse_dollar_sign(s, i, ms));
	free(out);
	return (tmp);
}

char *pq_add_quote(char *out, char *res)
{
	char *tmp;

	tmp = e_strjoin(out, res);
	free(res);
	free(out);
	return (tmp);
}

/*char *pq_add_tilda(char *out, char *s, int *i, t_ms *ms)
{
	return (e_strdup(find_in_env(ms, "HOME")));
}*/

char *parse_double_quote(char *s, int *i, t_ms *ms)
{
	int start;
	char *res;
	char *tmp;
	char *out;

	start = ++(*i);
	out = e_strdup("");
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '$')
			out = pq_add_var(out, s, i, ms);
		else
		{
			out = pq_add_char(out, s, i);
			(*i)++;
		}
	}
	return (out);
}

// "" -> > <
char *parse_quotes(char *s, t_ms *ms)
{
	int i;
	char *out;
	char *tmp;
	char *res;

	out = e_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			out = pq_add_quote(out, parse_single_quote(s, &i));
		else if (s[i] == '$')
			out = pq_add_var(out, s, &i, ms);
		else if (s[i] == '\"')
			out = pq_add_quote(out, parse_double_quote(s, &i, ms));
		else if (i == 0 && s[0] == '~' && (!s[1] || s[1] == ' ' || s[1] == '/'))
			out = e_strdup(find_in_env(ms, "HOME")); //pq_add_tilda(out, s, &i, ms);
		else
			out = pq_add_char(out, s, &i);
		i++;
	}
	free(s);
	return (out);
}

/*void tcmd_parse_quotes(t_ms *ms)
{
	t_cmd *p;
	char *pt;
	int i;
	
	if (!(p = tcmd_gotofirst(ms->cmd)))
		return ;
	while (p)
	{
		p->name = p->name ? parse_quotes(p->name, ms) : p->name;
		i = -1;
		while (p->flag && p->flag[++i])
			p->flag[i] = parse_quotes(p->flag[i], ms);
		i = -1;
		while (p->arg && p->arg[++i])
			p->arg[i] = parse_quotes(p->arg[i], ms);
		p->file = p->file ? parse_quotes(p->file, ms) : p->file;
		p = p->next;
	}
}*/

char **split_replace_quotes(char **s, t_ms *ms)
{
	int i;

	if (!s && !*s)
		return (s);
	i = 0;
	while (s[i])
	{
		s[i] = parse_quotes(s[i], ms);
		i++;
	}
	return (s);
}