#include "minishell.h"


t_cmd *tcmd_gotofirst(t_cmd *cmd)
{
	while (cmd->prev)
	{
		cmd = cmd->prev;
	}
	return (cmd);
}

/*
void tcmd_free(t_cmd *cmd)
{
	t_cmd *ptr;
	int i;

	if (!cmd)
		return ;
	tcmd_gotofirst(&cmd);
	while (cmd)
	{
		//charxxfree(cmd->flag);
		//charxxfree(cmd->arg);
		ptr = cmd;
		cmd = cmd->next;
		free(ptr);
	}
}

void tms_free(t_ms *ms)
{
	if (!ms)
		return ;
	//free(ms->line);
	//free(ms->path);
	tcmd_free(ms->cmd);
}
*/

void *e_malloc(size_t size)
{
	void *out;
	
	if (!(out = malloc(size)))
		throw_error(MEMALLOC);
	return (out);
}

void *e_calloc(size_t nmemb, size_t size)
{
	void *out;
	
	if (!(out = ft_calloc(nmemb, size)))
		throw_error(MEMALLOC);
	return (out);
}

char *e_strdup(char *s)
{
	char *out;
	
	if (!(out = ft_strdup(s)))
		throw_error(MEMALLOC);
	return (out);
}

char **e_split(char *s, char c)
{
	char **out;
	
	if (!(out = ft_split(s, c)))
		throw_error(MEMALLOC);
	return (out);
}

t_cmd *tcmd_init(t_ms *ms)
{
	t_cmd *cmd;
	int i;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		throw_error(MEMALLOC);
	cmd->name = NULL;
	cmd->flag = NULL;
	cmd->arg = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->prev = ms->cmd;
	if (ms->cmd)
		ms->cmd->next = cmd;
	return (cmd);
}

t_ms tms_init(void)
{
	t_ms ms;

	ms.line = NULL;
	ms.path = NULL;
	ms.cmd = NULL;
	ms.cmd = NULL; //tcmd_init(&ms);
	ms.env = NULL;
	return (ms);
}

void tcmd_print(t_cmd *cmd)
{
	int i = 0;
	cmd = tcmd_gotofirst(cmd);
	while (cmd)
	{
		printf("\nCMD #%d\n", i++);
		printf("name: %s\n", cmd->name);
		printf("Flags: ");
		for (int j=0; cmd->flag && cmd->flag[j]; j++)
			printf("%s ", cmd->flag[j]);
		printf("\nArgs: ");
		for (int j=0; cmd->arg && cmd->arg[j]; j++)
			printf("%s ", cmd->arg[j]);
		printf("\nPipe: %i\n", cmd->pipe);
		printf("Prev: %s, Next: %s\n",	cmd->prev ? "Yes" : "No", \
										cmd->next ? "Yes" : "No");
		cmd = cmd->next;
	}
}

int ft_striset(char *s, char *set)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int in_set(char c, char *set)
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


int split_validity_skip(char **s)
{
	if (!*s)
		return (0);
	while (*s && **s == ' ')
		s++;
	if (!*s)
		return (0);
	if (**s == '<' || **s == ';' || **s == '>')
		return (0);
	return (1);
}

int split_validity_less(char **s)
{
	if (!*s)
		return (0);
	if (**s == '<' || **s == ';')
		return (0);
	if (**s == '>')
	{
		if (split_validity_skip(s + 1))
			return (2);
		else
			return (0);
	}
	else if (**s == ' ')
		return (split_validity_skip(s));
	return (1);
}

int split_validity_greater(char **s)
{
	if (!*s)
		return (0);
	if (**s == '<' || **s == ';')
		return (0);
	else if (**(s) == '>' && **(s + 1) == '>')
		return (0);
	else if (**s == ' ')
		return (split_validity_skip(s));
	return (1);
}

int split_validity_semicolon(char **s)
{
	if (!*s)
		return (1);
	while (*s && **s == ' ')
		s++;
	if (*s && **s == ';')
		return (0);
	return (1);
}

int split_validity_pipe(char **s)
{
	if (!*s)
		return (0);
	while (*s && **s == ' ')
		s++;
	if (*s && (**s == '|' || **s == ';'))
		return (0);
	return (1);
}

int split_validity(char **s)
{
	while (*s)
	{
		if (**s == '<' && split_validity_less(s + 1) == 2)
			s++;
		else if (**s == '<' && !split_validity_less(s + 1))
			return (0);
		else if (**s == '>' && !split_validity_greater(s + 1))
			return (0);
		else if (**s == ';' && !split_validity_semicolon(s + 1))
			return (0);
		else if (**s == '|' && !split_validity_pipe(s + 1))
			return (0);
		s++;
	}
	return (1);
}

char **tcmd_skip(char **s)
{
	if (*s && **s == ' ')
	{
		while (*s && **s == ' ')
			s++;
	}
	return (s);
}

void tcmd_newtcmd(t_ms *ms)
{
	if (ms->cmd->name || ms->cmd->flag || ms->cmd->arg)
		ms->cmd = tcmd_init(ms);
}

char **tcmd_set_name(t_ms *ms, char **s)
{
	s = tcmd_skip(s);
	if (*s && **s == '>' && *(s + 1) && **(s + 1) == '>')
	{
		tcmd_newtcmd(ms);
		ms->cmd->name = ft_strdup(">>");
		return (s + 2);
	}
	else if (*s && **s == '<' && *(s + 1) && **(s + 1) == '>')
	{
		tcmd_newtcmd(ms);
		ms->cmd->name = ft_strdup("<>");
		return (s + 2);
	}
	else if (*s && **s != ';' && **s != '|')
	{
		tcmd_newtcmd(ms);
		ms->cmd->name = ft_strdup(*s);
		return (s + 1);
	}
	return (s);
}


int is_flag(char *s)
{
	if ((*s == '-' && ft_strlen(s) > 1 && !ft_strchr(s + 1, '-')) || \
		(*s == '-' && ft_strlen(s) > 2 && *(s + 1) == '-' && !ft_strchr(s + 2, '-'))) // --leak-check=full ????? '-' in middle flag
		return (1);
	return (0);
}

char **tcmd_addflag(t_ms *ms, char **s)
{
	int i;

	i = 0;
	while (ms->cmd->flag[i])
		i++;
	ms->cmd->flag[i] = e_strdup(*s);
	return (s + 1);
}

char **tcmd_addarg(t_ms *ms, char **s)
{
	int i;

	i = 0;
	while (ms->cmd->arg[i])
		i++;
	ms->cmd->arg[i] = e_strdup(*s);
	return (s + 1);
}

char **tcmd_semicolon(t_ms *ms, char **s)
{
	s = tcmd_skip(s);
	if (*s && **s == ';')
	{
		if (!ms->cmd->name && !ms->cmd->flag && !ms->cmd->arg)
			throw_error(PARSEERR);
		//tcmd_newtcmd(ms);
		//tcmd_newtcmd(ms);
		ms->cmd = tcmd_init(ms);
		ms->cmd = tcmd_init(ms);
		return (s + 1);
	}
	return (s);
}

char **tcmd_pipe(t_ms *ms, char **s)
{
	s = tcmd_skip(s);
	if (*s && **s == '|')
	{
		ms->cmd->pipe = 1;
		return (s + 1);
	}
	return (s);
}

int split_countflags(char **s)
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

int split_countargs(char **s)
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

char **charxx_alloc(int size)
{
	char **out;

	out = NULL;
	if (size > 0)
	{
		if (!(out = (char **)malloc(sizeof(char *) * (size + 1))))
			throw_error(MEMALLOC);
		while (size >= 0)
			out[size--] = NULL;
	}
	return (out);
}

void tcmd_set(t_ms *ms, char **s)
{
	while (*s)
	{
		s = tcmd_semicolon(ms, s);
		s = tcmd_set_name(ms, s);
		ms->cmd->flag = charxx_alloc(split_countflags(s));
		while ((s = tcmd_skip(s)) && *s && is_flag(*s))
			s = tcmd_addflag(ms, s);
		ms->cmd->arg = charxx_alloc(split_countargs(s));
		while ((s = tcmd_skip(s)) && *s)
		{
			if (!in_set(**s, SET))
				s = tcmd_addarg(ms, s);
			else
				break ;
		}
		s = tcmd_pipe(ms, s);
	}
}

void charxx_free(char **s)
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

int tcmd_isempty(t_cmd *cmd)
{
	if (cmd->name || cmd->flag || cmd->arg)
		return (0);
	return (1);
}

t_cmd *tcmd_delete_cmd(t_ms *ms, t_cmd *ptr)
{
	t_cmd *next;

	if (ms->cmd == ptr) //mb error here - them not equal
	{
		if (ms->cmd->next)
			ms->cmd = ms->cmd->next;
		else if (ms->cmd->prev)
			ms->cmd = ms->cmd->prev;
	}
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	else if (ptr->prev)
		ptr->prev->next = ptr->next;
	next = ptr->next;
	free(ptr->name);
	charxx_free(ptr->flag);
	charxx_free(ptr->arg);
	free(ptr);
	return (next);
}
/*
t_cmd *tcmd_opt_less(t_ms *ms, t_cmd *ptr)
{
	if (ms->cmd->prev && tcmd_isempty(ms->cmd->prev)) // !ms->cmd->prev->name)
		return (tcmd_delete_cmd(ms, ptr));
	else if ()
	//return (NULL);
}

void tcmd_optimize(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr && !ft_strcmp(ptr->name, "<"))
			ptr = tcmd_opt_less(ms, ptr);
	}
}
*/
void tms_lineparse(t_ms *ms)
{
	char **split;

	if (!(split = ft_splitset(ms->line, SET)))
		throw_error(MEMALLOC);
	if (!split_validity(split))
		throw_error(PARSEERR);
	ms->cmd = ms->cmd ? ms->cmd : tcmd_init(ms);
	tcmd_set(ms, split);
	charxx_free(split);
	//tcmd_optimize(ms);
}

/*
int main(int argc, char **argv, char **env)
{
	t_ms ms;

	ms = tms_init();
	//ms.cmd = tcmd_init(&ms);

	ms.line = ft_strdup("cat -t -v b<a | man <> a  > b; cat m>>a;   yu  --leak -n -n-n ans;>b;<rt; ");
	tms_lineparse(&ms);
	
	tcmd_print(ms.cmd);

	//exit(EXIT_SUCCESS);
	return (0);
}
*/