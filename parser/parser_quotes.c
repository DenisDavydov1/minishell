#include "../minishell.h"

int charxx_in_set(char *s, char *set)
{
	int i;

	i = 0;
	while (s && *s)
	{
		i = -1;
		while (set[++i])
		{
			if (*s == set[i])
				return (1);
		}
		s++;
	}
	return (0);
}

char *parse_dollar_sign(char *s, int *i, t_ms *ms)
{
	int start;
	char *name;
	char *value;

	start = ++(*i);
	while (s[*i] && !in_set(s[*i], QUOTES) && !in_set(s[*i], SET))
		(*i)++;
	name = e_substr(s, start, *i - start); //mb *i - 1
	value = find_in_env(ms, name);
	//printf("%s\n", name);
	free(name);
	//printf("%s\n", value);
	return (value ? value : "");
}

char *parse_single_quote(char *s, int *i)
{
	int start;

	start = ++(*i);
	while (s[*i] != '\'')
		(*i)++;
	return (e_substr(s, start, *i - start)); //mb *i - 1
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
		//printf("%c\n", s[i]);
		if (s[i] == '\'')
		{
			res = parse_single_quote(s, &i);
			tmp = e_strjoin(out, res);
			free(res);
			free(out);
			out = tmp;
		}
		else if (s[i] == '$')
		{
			
			res = parse_dollar_sign(s, &i, ms);
			tmp = e_strjoin(out, res);
			free(out);
			out = tmp;
		}
		/*else if (*s = "\"")
		{
			res = parse
		}*/
		else
		{
			tmp = e_calloc(ft_strlen(out) + 2, sizeof(char));
			ft_strlcat(tmp, out, ft_strlen(out) + 1);
			ft_strlcat(tmp, &s[i], ft_strlen(out) + 2);
			free(out);
			out = tmp;
		}
		
		i++;
	}
	free(s);
	//printf("new_string: %s\n", out);
	return (out);
}

void tcmd_parse_quotes(t_ms *ms)
{
	t_cmd *p;
	
	if (!(p = tcmd_gotofirst(ms->cmd)))
		return ;
	while (p)
	{
		p->name = p->name ? parse_quotes(p->name, ms) : p->name;
		p = p->next;
	}
}