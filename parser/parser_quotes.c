#include "../minishell.h"

/*char *parse_dollar_sign_in_loop(t_ms *ms)
{
	char *out;

	if (ms->cmd->name && in_set('$', ) && *(ft_strchr(ms->cmd->name, '$') + 1) = '?')
	if (s[*i] == '?' && ++(*i))
		return (e_itoa(ms->cmd->ret));
}*/

char *parse_dollar_sign(char *s, int *i, t_ms *ms)
{
	int start;
	char *name;
	char *value;

	start = ++(*i);
	if (s[*i] == '?')
		return (e_itoa(ms->ret));
	while (s[*i] && !in_set(s[*i], QUOTES) && !in_set(s[*i], SET) && s[*i] != '$')
		(*i)++;
	(*i)--;
	name = e_substr(s, start, *i - start); //mb *i - 1
	value = find_in_env(ms, name);
	free(name);
	return (value ? e_strdup(value) : e_strdup(""));
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
	char *res;

	if (!s[*i + 1] || s[*i + 1] == ' ' || s[*i + 1] == '\'' || \
		s[*i + 1] == '\"' || s[*i + 1] == '$')
	{
		res = e_strdup("$");
	}
	else
		res = parse_dollar_sign(s, i, ms);
	tmp = e_strjoin(out, res);
	//printf("tmp: [%c][%c][%c]\n", tmp[0] ? tmp[0] : '0', tmp[1] ? tmp[1] : '0', tmp[2] ? tmp[2] : '0');
	free(res);
	//printf("1 ");
	free(out);
	//printf("2\n");
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

char *pq_add_slash(char *out, char *s, int *i)
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
		else if (s[*i] == '\\')
			out = pq_add_slash(out, s, i);
		else
			out = pq_add_char(out, s, i);
		(*i)++;
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

	//printf("before: >%s< ", s);
	out = e_strdup("");
	i = 0;
	//printf("[%c][%c][%c]\n", s[0] ? s[0] : '0', s[1] ? s[1] : '0', s[2] ? s[2] : '0');
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
		else if (s[i] == '\\')
			out = pq_add_slash(out, s, &i);
		else
			out = pq_add_char(out, s, &i);
		i++;
	}
	free(s);
	//printf("[%c][%c][%c]\n", out[0] ? out[0] : '0', out[1] ? out[1] : '0', out[2] ? out[2] : '0');
	//printf("after: >%s< \n", out);
	return (out);
}

void tcmd_parse_quotes(t_ms *ms)
{
	t_cmd *p;
	char *pt;
	int i;
	
	p = ms->cmd;
	//printf("before: >%s< ", p->name);
	//printf("name: [%s]...", p->name);
	p->name = p->name ? parse_quotes(p->name, ms) : p->name;
	//printf("OK\n");
	//printf("after: >%s< \n", p->name);
	i = -1;
	while (p->flag && p->flag[++i])
		p->flag[i] = parse_quotes(p->flag[i], ms);
	i = -1;
	while (p->arg && p->arg[++i])
	{
		//printf("arg: [%s]...", p->arg[i]);
		p->arg[i] = parse_quotes(p->arg[i], ms);
		//printf("OK\n");
	}
	p->file = p->file ? parse_quotes(p->file, ms) : p->file;
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

/*
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
}*/