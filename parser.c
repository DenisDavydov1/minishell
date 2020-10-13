#include "minishell.h"


t_cmd *tcmd_gotofirst(t_cmd *cmd)
{
	while (cmd->prev)
	{
		cmd = cmd->prev;
	}
	return (cmd);
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

void tcmd_free(t_cmd *cmd)
{
	t_cmd *ptr;
	int i;

	if (!cmd)
		return ;
	cmd = tcmd_gotofirst(cmd);
	while (cmd)
	{
		free(cmd->name);
		charxx_free(cmd->flag);
		charxx_free(cmd->arg);
		ptr = cmd;
		cmd = cmd->next;
		free(ptr);
	}
}

void tcmd_free_one(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->name);
	charxx_free(cmd->flag);
	charxx_free(cmd->arg);
	free(cmd);
}

/*
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


t_cmd *tcmd_insert(t_cmd *to)
{
	t_cmd *cmd;
	t_cmd *t;
	int i;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		throw_error(MEMALLOC);
	cmd->name = NULL;
	cmd->flag = NULL;
	cmd->arg = NULL;
	cmd->pipe = 0;
	if (to->next)
	{
		t = to->next;
		to->next->prev = cmd;
		to->next = cmd;
		cmd->next = t;
		cmd->prev = to;
	}
	else
	{
		to->next = cmd;
		cmd->prev = to;
	}
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
		printf("\nAddr: %p\n", cmd);
		printf("Prev: %p, Next: %p\n",	cmd->prev ? cmd->prev : 0, \
										cmd->next ? cmd->next : 0);
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

void tcmd_replace_lg(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->name && !ft_strcmp(cmd->name, "<>"))
		{
			free(cmd->name);
			cmd->name = e_strdup("<");
		}
		cmd = cmd->next;
	}
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

	if (ms->cmd == ptr)
	{
		if (ms->cmd->next)
			ms->cmd = ms->cmd->next;
		else if (ms->cmd->prev)
			ms->cmd = ms->cmd->prev;
	}
	if (ptr->next)
	{
		ptr->next->prev = ptr->prev;
		if (ptr->prev)
			ptr->prev->next = ptr->next;
	}	
	else if (ptr->prev)
	{
		ptr->prev->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
	}	
	next = ptr->next;
	tcmd_free_one(ptr);
	return (next);
}

t_cmd *tcmd_gotoempty(t_cmd *cmd)
{
	while (cmd && !tcmd_isempty(cmd) && cmd->next) // danger zone (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

t_cmd *tcmd_gotolast(t_cmd *cmd, char *s)
{
	cmd = tcmd_gotoempty(cmd);
	while (cmd)
	{
		if (!cmd->name && cmd->prev)
			cmd = cmd->prev;
		else if (cmd->name && ft_strcmp(cmd->name, s) && cmd->prev)
			cmd = cmd->prev;
		else
			break ;
	}
	return (cmd);
}

t_cmd *tcmd_opt_less_greater(t_ms *ms, t_cmd *ptr)
{
	t_cmd *tmp_last;
	t_cmd *tmp_cur;

	if (*(ptr->name) == '<' && ((ptr->prev && tcmd_isempty(ptr->prev)) || !ptr->prev)) // !ms->cmd->prev->name)
		return (tcmd_delete_cmd(ms, ptr));
	if (*(ptr->name) == '>' && ((ptr->prev && tcmd_isempty(ptr->prev)) || !ptr->prev))
		return ((ptr = tcmd_insert(ptr)));
	else if (ptr->next)
	{
		tmp_last = tcmd_gotolast(ptr, ptr->name);
		tmp_cur = ptr;
		while (tmp_cur && tmp_cur != tmp_last)
		{
			if (!ft_strcmp(tmp_cur->name, ptr->name))
				tmp_cur = tcmd_delete_cmd(ms, tmp_cur);
			else
				tmp_cur = tmp_cur->next;
		}
	}
	return (ptr->next);
}









void tcmd_remove_nulls(t_ms *ms)
{
	t_cmd *ptr;
	int i = 0;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		//printf("\n!\n");
		if (tcmd_isempty(ptr))
			ptr = tcmd_delete_cmd(ms, ptr);
		else
			ptr = ptr->next;
		//printf("%d %p\n", i, ptr ? ptr : 0);
	}
	
}

void tcmd_optimize(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	tcmd_replace_lg(ptr);
	while (ptr)
	{
		if (ptr && ptr->name && (!ft_strcmp(ptr->name, "<") || !ft_strcmp(ptr->name, ">")))
			ptr = tcmd_opt_less_greater(ms, ptr);
		else
			ptr = ptr->next;
	}
	//tcmd_remove_nulls(ms);
}












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
	tcmd_optimize(ms);
	
}


int main(int argc, char **argv, char **env)
{
	t_ms ms;

	ms = tms_init();
	//ms.cmd = tcmd_init(&ms);

	ms.line = ft_strdup("tye >a >b ; <a<b; >b>t"); // <a, <a<b
	tms_lineparse(&ms);
	
	
	tcmd_print(ms.cmd);

	//exit(EXIT_SUCCESS);
	return (0);
}
