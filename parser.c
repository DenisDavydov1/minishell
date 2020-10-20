#include "minishell.h"


t_cmd *tcmd_gotofirst(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
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

void tcmd_free(t_ms *ms)
{
	t_cmd *ptr;

	if (!ms->cmd)
		return ;
	ms->cmd = tcmd_gotofirst(ms->cmd);
	while (ms->cmd)
	{
		free(ms->cmd->name);
		free(ms->cmd->file);
		charxx_free(ms->cmd->flag);
		charxx_free(ms->cmd->arg);
		ptr = ms->cmd;
		ms->cmd = ms->cmd->next;
		free(ptr);
	}
	ms->cmd = NULL;
}

void tcmd_free_one(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->name);
	free(cmd->file);
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
		throw_error(MEMALLOC, NULL);
	return (out);
}

void *e_calloc(size_t nmemb, size_t size)
{
	void *out;
	
	if (!(out = ft_calloc(nmemb, size)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char *e_strdup(char *s)
{
	char *out;
	
	if (!(out = ft_strdup(s)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char **e_split(char *s, char c)
{
	char **out;
	
	if (!(out = ft_split(s, c)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char *e_substr(char *s, int start, int len)
{
	char *out;
	
	if (!(out = ft_substr((char const *)s, (unsigned int)start, (size_t)len)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char *e_strjoin(char *s1, char *s2)
{
	char *out;
	
	if (!(out = ft_strjoin((char const *)s1, (char const *)s2)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char *e_itoa(int n)
{
	char *out;
	
	if (!(out = ft_itoa(n)))
		throw_error(MEMALLOC, NULL);
	return (out);
}


t_cmd *tcmd_init(t_ms *ms)
{
	t_cmd *cmd;
	int i;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		throw_error(MEMALLOC, NULL);
	cmd->name = NULL;
	cmd->flag = NULL;
	cmd->arg = NULL;
	cmd->pipe = 0;
	cmd->write = 0;
	cmd->fd = 1;
	cmd->file = NULL;
	cmd->pfd[0] = 0;
	cmd->pfd[1] = 1;
	cmd->next = NULL;
	cmd->prev = ms->cmd;
	if (ms->cmd)
	{
		ms->cmd->next = cmd;
	}
	return (cmd);
}


t_cmd *tcmd_insert(t_cmd *to)
{
	t_cmd *cmd;
	t_cmd *t;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		throw_error(MEMALLOC, NULL);
	cmd->name = NULL;
	cmd->flag = NULL;
	cmd->arg = NULL;
	cmd->pipe = 0;
	cmd->write = 0;
	cmd->fd = 1;
	cmd->file = NULL;
	cmd->pfd[0] = 0;
	cmd->pfd[1] = 1;
	cmd->prev = NULL;
	cmd->next = NULL;
	if (to->next)
	{
		t = to->next;
		to->next = cmd;
		cmd->next = t;
		t->prev = cmd;
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
	ms.cmd = NULL;
	ms.env = NULL;
	ms.ret = 0;
	return (ms);
}

void tcmd_print(t_cmd *cmd)
{
	int i = 0;
	if (!cmd)
	{
		printf("NO CMD");
		return ;
	}
	cmd = tcmd_gotofirst(cmd);
	while (cmd)
	{
		printf("\nCMD #%d\n", i++);
		printf("Name: %s\n", cmd->name);
		printf("Flags: ");
		for (int j=0; cmd->flag && cmd->flag[j]; j++)
			printf("%s ", cmd->flag[j]);
		printf("\nArgs: ");
		for (int j=0; cmd->arg && cmd->arg[j]; j++)
			printf("%s ", cmd->arg[j]);
		printf("\nPipe: %i\n", cmd->pipe);
		printf("Write: %i (%s)\n", cmd->write, cmd->write ? \
			(cmd->write == 1 ? "write to file" : "append to file" ) : "write to stdout");
		printf("File: %s\n", cmd->file);
		//printf("\nAddr: %p\n", cmd);
		//printf("Prev: %p, Next: %p\n",	cmd->prev ? cmd->prev : 0, \
		//								cmd->next ? cmd->next : 0);
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
	if (*s == '\"' || *s == '\'')
		s++;
	if ((*s == '-' && ft_strlen(s) > 1 && !ft_strchr(s + 1, '-')) || \
		(*s == '-' && ft_strlen(s) > 2 && *(s + 1) == '-' && !ft_strchr(s + 2, '-')))
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
		if (!ms->cmd->name && !ms->cmd->flag && !ms->cmd->arg && throw_error(PARSEERR, ms))
			return (NULL);
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
		ms->cmd = tcmd_init(ms);
		ms->cmd = tcmd_init(ms);
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
			throw_error(MEMALLOC, NULL);
		while (size >= 0)
			out[size--] = NULL;
	}
	return (out);
}

int tcmd_set(t_ms *ms, char **s)
{
	while (*s)
	{
		if (!(s = tcmd_semicolon(ms, s))) // may be lost pointer s
			return (0);
		s = tcmd_set_name(ms, s);
		//s = tcmd_semicolon(ms, s);
		//s = tcmd_set_name(ms, s);
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
	return (1);
}

int charxx_len(char **ss)
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

char **charxx_insert(char **ss, char *s, int pos)
{
	char **out;
	int i;

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

char **charxx_delete_one(char **ss, int pos)
{
	char **out;
	int i;

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







void tcmd_replace_lg(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && !ft_strcmp(ptr->name, "<>"))
		{
			free(ptr->name);
			ptr->name = e_strdup("<");
		}
		ptr = ptr->next;
	}
}

int tcmd_isempty(t_cmd *cmd)
{
	if (cmd->name || (cmd->flag && *cmd->flag) || (cmd->arg && *cmd->arg))
		return (0);
	return (1);
}

int tcmd_delete_cmd_if_equal(t_ms *ms)
{
	if (ms->cmd->next)
		ms->cmd = ms->cmd->next;
	else if (ms->cmd->prev)
		ms->cmd = ms->cmd->prev;
	else
	{
		tcmd_free(ms);
		return (1);
	}
	return (0);
}

t_cmd *tcmd_delete_cmd(t_ms *ms, t_cmd *ptr)
{
	t_cmd *next;

	if (ms->cmd == ptr)
		if (tcmd_delete_cmd_if_equal(ms))
			return (NULL);
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

t_cmd *tcmd_write_empty_file(t_ms *ms, t_cmd *ptr)
{
	ptr->write = 1;
	ptr = tcmd_insert(ptr);
	return (ptr->next);
}











void tcmd_remove_nulls(t_ms *ms)
{
	t_cmd *ptr;

	if (!ms->cmd)
		return ;
	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (tcmd_isempty(ptr))
			ptr = tcmd_delete_cmd(ms, ptr);
		else
			ptr = ptr->next;
	}
}

void tcmd_flags_to_args(t_ms *ms)
{
	int i;
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && in_set(*ptr->name, SET) && ptr->flag)
		{
			i = 0;
			while (ptr->flag[i])
			{
				ptr->arg = charxx_insert(ptr->arg, ptr->flag[i], i);
				free(ptr->flag[i]);
				ptr->flag[i] = NULL;
				i++;
			}
		}
		ptr = ptr->next;
	}
}

t_cmd *tcmd_has_cmd(t_cmd *cmd)
{
	while (cmd && cmd->prev && ((!cmd->name && cmd->arg) || (cmd->name && in_set(*cmd->name, SET))))
	{
		cmd = cmd->prev;
	}
	if (cmd->name && !in_set(*cmd->name, SET))
		return (cmd);
	else
		return (0);
}

t_cmd *tcmd_make_cmd(t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	cmd->name = e_strdup(cmd->arg[i++]);
	while (is_flag(cmd->arg[i]))
	{
		cmd->flag = charxx_insert(cmd->flag, cmd->arg[i], i - 1);
		i++;
	}
	j = 0;
	while (cmd->arg[i])
	{
		free(cmd->arg[j]);
		cmd->arg[j] = e_strdup(cmd->arg[i]);
		free(cmd->arg[i]);
		cmd->arg[i] = NULL;
		j++;
		i++;
	}
	return (cmd);
}

void tcmd_divide_args(t_ms *ms)
{
	int i;
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && in_set(*ptr->name, SET) && ptr->arg && charxx_len(ptr->arg) > 1)
		{
			ptr = tcmd_insert(ptr);
			ptr->pipe = ptr->prev->pipe;
			ptr->prev->pipe = 0;
			i = 1;
			while (ptr->prev->arg[i])
			{
				ptr->arg = charxx_insert(ptr->arg, ptr->prev->arg[i], i - 1);
				free(ptr->prev->arg[i]);
				ptr->prev->arg[i] = NULL;
				i++;
			}
			if (!tcmd_has_cmd(ptr->prev))
				ptr = tcmd_make_cmd(ptr);
		}
		ptr = ptr->next;
	}
}

void tcmd_put_args_to_cmd(t_ms *ms)
{
	int i;
	t_cmd *ptr;
	t_cmd *ptr_cmd;
	t_cmd *ptr_last;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (tcmd_isempty(ptr) || (ptr->name && in_set(*ptr->name, SET)))
		{
			ptr = ptr->next;
			continue ;
		}
		ptr_cmd = ptr;
		ptr_last = tcmd_gotoempty(ptr);
		while (ptr)
		{
			if (!ptr->name && ptr->arg)
			{
				i = -1;
				while (ptr->arg[++i])
				{
					ptr_cmd->arg = charxx_insert(ptr_cmd->arg, ptr->arg[i], charxx_len(ptr_cmd->arg));
					free(ptr->arg[i]);
					ptr->arg[i] = NULL;
				}
				ptr = tcmd_delete_cmd(ms, ptr);
			}
			if (ptr == ptr_last)
				break ;
			ptr = ptr ? ptr->next : ptr;
		}
		ptr = ptr ? ptr->next : ptr;
	}
}

void tcmd_move_pipes(t_ms *ms)
{
	int i;
	t_cmd *ptr;
	t_cmd *ptr_cur;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->pipe && (!ptr->name || (ptr->name && in_set(*ptr->name, SET))))
		{
			ptr_cur = ptr;
			while (ptr_cur->prev && !tcmd_isempty(ptr_cur->prev) && \
				(!ptr_cur->name || (ptr_cur->name && in_set(*ptr_cur->name, SET))))
				ptr_cur = ptr_cur->prev;
			if (!in_set(*ptr_cur->name, SET))
			{
				ptr->pipe = 0;
				ptr_cur->pipe = 1;
			}
		}
		ptr = ptr->next;
	}
}

t_cmd *tcmd_get_cmd(t_cmd *cmd)
{
	while (cmd && cmd->prev && !tcmd_isempty(cmd->prev))
	{
		cmd = cmd->prev;
	}
	return (cmd);
}


void tcmd_set_write_files(t_ms *ms)
{
	t_cmd *ptr;
	t_cmd *ptr_cmd;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && !ft_strcmp(ptr->name, ">"))
		{
			ptr_cmd = tcmd_get_cmd(ptr);
			if (ptr_cmd->file)						//
				printf("Write file conflict\n");	//to delete
			ptr_cmd->file = e_strdup(*ptr->arg);
			ptr_cmd->write = 1;
			ptr = tcmd_delete_cmd(ms, ptr);

		}
		else if (ptr->name && !ft_strcmp(ptr->name, ">>"))
		{
			ptr_cmd = tcmd_get_cmd(ptr);
			if (ptr_cmd->file)						//
				printf("Write file conflict\n");	//to delete
			ptr_cmd->file = e_strdup(*ptr->arg);
			ptr_cmd->write = 2;
			ptr = tcmd_delete_cmd(ms, ptr);
		}
		else
			ptr = ptr->next;
	}
}


t_cmd *tcmd_opt_less(t_ms *ms, t_cmd *ptr)
{
	t_cmd *ptr_cmd;
	t_cmd *ptr_last;

	if ((ptr_cmd = tcmd_has_cmd(ptr)) && (!ptr_cmd->arg || (ptr_cmd->arg && !*ptr_cmd->arg)))
	{
		ptr_last = tcmd_gotolast(ptr, "<");
		ptr_cmd->arg = charxx_insert(ptr_cmd->arg, *ptr_last->arg, 0);
		ptr_last = tcmd_delete_cmd(ms, ptr_last);
		return (ptr->next);
	}

	return (ptr->next);
}

t_cmd *tcmd_opt_greater(t_ms *ms, t_cmd *ptr)
{
	t_cmd *tmp;
	t_cmd *tmp_cmd;

	if (!ptr->prev || (ptr->prev && tcmd_isempty(ptr->prev)))
		return ((ptr = tcmd_insert(ptr)));
	else
	{
		tmp = tcmd_gotoempty(ptr);
		tmp = tmp->name ? tmp : tmp->prev;
		while (tmp && tmp->name && tmp->prev && tmp->prev->name && *tmp->name != '>')
			tmp = tmp->prev;
		tmp_cmd = tmp;
		while (tmp_cmd && tmp_cmd->name && tmp_cmd->prev && tmp_cmd->prev->name && in_set(*tmp_cmd->name, SET))
			tmp_cmd = tmp_cmd->prev;
		if (tmp_cmd && tmp_cmd->name && !in_set(*tmp_cmd->name, SET) && !tmp_cmd->file)
		{
			
			tmp_cmd->file = e_strdup(*tmp->arg);
			tmp_cmd->write = !ft_strcmp(tmp->name, ">>") ? 2 : 1;
			tmp = tcmd_delete_cmd(ms, tmp);
			return (ptr);
		}
		else if (tmp_cmd && (!tmp_cmd->name || (tmp_cmd->name && in_set(*tmp_cmd->name, SET))))
		{

		}
	}
	return (ptr->next);
}


void tcmd_optimize_signs(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr && ptr->name && !ft_strcmp(ptr->name, "<"))
			ptr = tcmd_opt_less(ms, ptr);
		else if (ptr && ptr->name && (!ft_strcmp(ptr->name, ">" ) || !ft_strcmp(ptr->name, ">>")))
			ptr = tcmd_opt_greater(ms, ptr);
		else
			ptr = ptr->next;
	}
}

void tcmd_put_arg_to_name(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->prev && tcmd_isempty(ptr->prev) && !tcmd_isempty(ptr) && \
			!ptr->name && ptr->arg && *ptr->arg)
		{
			//printf("argtname: %s\n", *ptr->arg);
			ptr->name = e_strdup(*ptr->arg);
			ptr->arg = charxx_delete_one(ptr->arg, 0);
		}
		ptr = ptr->next;
	}
}
/*
void tcmd_put_input_args_to_cmd(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && *ptr->name == '<' && ptr->arg && ptr->prev && \
			ptr->prev->name && !in_set(*ptr->prev->name, SET))
		{
			if (!ptr->prev->arg || (ptr->prev->arg && !*ptr->prev->arg))
				ptr->prev->arg = charxx_insert(ptr->prev->arg, *ptr->arg, 0);
			ptr = tcmd_delete_cmd(ms, ptr);
		}
		else
		{
			ptr = ptr->next;
		}
	}
}*/

void tcmd_set_echo_err_a(t_ms *ms, t_cmd *p)
{
	t_cmd *p_cmd;
	int pipe;

	p_cmd = tcmd_get_cmd(p);
	while (p_cmd && p_cmd)
	{
		if (p_cmd->pipe == 1)
			pipe = 1;
		if (p_cmd == p)
			p_cmd = p_cmd->next;
		else
			p_cmd = tcmd_delete_cmd(ms, p_cmd);
		if (!p_cmd || (tcmd_isempty(p_cmd) && pipe == 0))
			break ;
		else if (tcmd_isempty(p_cmd) && pipe == 1 && !(pipe = 0))
			p_cmd = p_cmd->next;
	}
}

void tcmd_set_echo_err(t_ms *ms, t_cmd *p, char *errtype)
{
	t_cmd *p_cmd;
	int len;

	p = tcmd_insert(p);
	//ms->ret = 1;
	p->name = e_strdup("echo");
	p->arg = charxx_alloc(2);
	*p->arg = e_calloc(12 + ft_strlen(*p->prev->arg) + ft_strlen(errtype), sizeof(char));
	ft_strlcat(*p->arg, "minishell: ", (len = ft_strlen("minishell: ") + 1));
	ft_strlcat(*p->arg, *p->prev->arg, (len += ft_strlen(*p->prev->arg) + 1));
	ft_strlcat(*p->arg, errtype, (len += ft_strlen(errtype) + 1));
	tcmd_set_echo_err_a(ms, p);
}

void tcmd_open_create_files(t_ms *ms)
{
	t_cmd *ptr;
	int fd;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && !ft_strcmp(ptr->name, "<") && ptr->arg && *ptr->arg)
		{
			fd = open(*ptr->arg, O_RDONLY);
			if (fd < 0)
				tcmd_set_echo_err(ms, ptr, CDERR);
			else
				close(fd);
		}
		else if (ptr->name && (!ft_strcmp(ptr->name, ">") || \
			!ft_strcmp(ptr->name, ">>") || !ft_strcmp(ptr->name, "<>")) && \
			ptr->arg && *ptr->arg)
		{
			fd = open(*ptr->arg, O_CREAT, 0644);
			if (fd < 0)
				tcmd_set_echo_err(ms, ptr, CDERR);
			else
				close(fd);
		}
		ptr = ptr->next;
	}
}

/*
void tcmd_open_create_files(t_ms *ms)
{
	t_cmd *ptr;
	int fd;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && !ft_strcmp(ptr->name, "<") && ptr->arg && *ptr->arg)
		{
			if ((fd = open(*ptr->arg, O_RDONLY) < 0))
				tcmd_set_echo_err(ms, ptr, CDERR);
			else
			{
				printf("file closed\n");
				close(fd);
			}	
		}
		else if (ptr->name && (!ft_strcmp(ptr->name, ">") || \
			!ft_strcmp(ptr->name, ">>") || !ft_strcmp(ptr->name, "<>")) && \
			ptr->arg && *ptr->arg)
		{
			if ((fd = open(*ptr->arg, O_CREAT, 0644) < 0))
				tcmd_set_echo_err(ms, ptr, CDERR);
			else
			{
				printf("file closed\n");
				close(fd);
			}
		}
		ptr = ptr->next;
	}
}*/

void tcmd_remove_signs(t_ms *ms)
{
	t_cmd *p;

	p = tcmd_gotofirst(ms->cmd);
	while (p)
	{
		if (p->name && in_set(*p->name, SET))
			p = tcmd_delete_cmd(ms, p);
		else
			p = p->next;
	}
}

void tcmd_optimize(t_ms *ms)
{
	//t_cmd *ptr;

	if (!ms->cmd)
		return ;
	//ptr = tcmd_gotofirst(ms->cmd);
	//tcmd_replace_lg(ms);
	tcmd_move_pipes(ms);
	tcmd_flags_to_args(ms);
	tcmd_divide_args(ms);
	tcmd_put_arg_to_name(ms);
	tcmd_put_args_to_cmd(ms);
	tcmd_open_create_files(ms);
	tcmd_replace_lg(ms);
	tcmd_optimize_signs(ms);
	tcmd_remove_nulls(ms);
	tcmd_remove_signs(ms);
	//tcmd_set_write_files(ms);

	

	//tcmd_parse_quotes(ms);
	//tcmd_put_input_args_to_cmd(ms);
	//tcmd_print(ms->cmd);

	ms->cmd = tcmd_gotofirst(ms->cmd);
}







/*
** SPLIT_SET
*/

static char	**free_arr(char **arr)
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
/*
static int in_set(char c, char *set)
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
}*/

int get_quote_end(char *s, char quote, int start)
{
	int end;

	end = start + 1;
	while (s && s[end] && s[end] != quote)
		end++;
	if (s[end] == quote)
	{
		//while (s[end + 1] && !in_set(s[end + 1], SET))
			//end++;
		return (end);
	}
	else
		return (0);
}
/*
static char	**arralloc(char *s, char *set)
{
	int words;
	int added;
	int i;

	if (!s)
		return (NULL);
	words = 0;
	added = 0;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if ((i = get_quote_end(s, s[i], i)) && ++words)
				added = 0;
			else
				return (NULL);
		}
		else if (in_set(s[i], set) && ++words)
			added = 0;
		else if (!added && ++words)
			added = 1;
	}
	//printf("words: %d\n", words);
	return ((char **)e_malloc((words + 1) * sizeof(char *)));
}*/
/*
static char	**arralloc(char *s, char *set)
{
	int words;
	int added;
	int i;

	if (!s)
		return (NULL);
	words = 0;
	added = 0;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if ((i = get_quote_end(s, s[i], i)))
				added = 1;
			else
				return (NULL);
		}
		else if (in_set(s[i], set) && ++words)
			added = 0;
		else if (!added && ++words)
			added = 1;
	}
	//printf("words: %d\n", words);
	return ((char **)e_malloc((words + 1) * sizeof(char *)));
}*/

static char	**arralloc(char *s, char *set)
{
	int words;
	int added;
	int i;

	if (!s)
		return (NULL);
	words = 0;
	added = 1;
	i = -1;
	while (s && s[++i])
	{
		if (!s[i + 1])
			words++;
		if (in_set(s[i], set))
		{
			words += added ? 1 : 2;
			added = 1;
		}
		else if (s[i] == '\'' || s[i] == '\"')
		{
			if (!(i = get_quote_end(s, s[i], i)))
				return (NULL);
			added = 0;
		}
		else
			added = 0;
	}
	//printf("words: %d\n", words);
	return ((char **)e_malloc((words + 1) * sizeof(char *)));
}

char		**e_splitset(char *s, char *set)
{
	char	**out;
	char	**word_pt;
	size_t	start;
	size_t	end;

	if (!(out = arralloc(s, set)))
		return (NULL);
	word_pt = out;
	start = 0;
	end = 0;
	while (s[start])
	{
		if (s[end] == '\'' || s[end] == '\"')
		{
			end = get_quote_end(s, s[end], end) + 1;
			if (s[end] && !in_set(s[end], set))
				continue ;
		}
		else if (in_set(s[end], set))
			end++;
		else
		{
			while (s[end] && !in_set(s[end], set) && s[end] != '\'' && s[end] != '\"')
				end++;
			if (s[end] && !in_set(s[end], set) && (s[end] == '\'' || s[end] == '\"'))
				continue ;
		}
		if (start < end)
			if (!(*word_pt++ = ft_substr(s, (unsigned int)start, end - start)))
				return (free_arr(out));
		start = end;
	}
	*word_pt = NULL;
	return (out);
}


/*
**
*/




int tms_lineparse(t_ms *ms)
{
	char **split;

	if (!(split = e_splitset(ms->line, SET)) && throw_error(PARSEERR, ms))
		return (0);
	if (!split_validity(split) && throw_error(PARSEERR, ms))
		return (0);
	//split = split_replace_quotes(split, ms);
	ms->cmd = ms->cmd ? ms->cmd : tcmd_init(ms);
	if (!tcmd_set(ms, split))
	{
		charxx_free(split);
		return (0);
	}
	charxx_free(split);
	tcmd_optimize(ms);
	return (1);
}

/*
int main(int argc, char **argv, char **env)
{
	t_ms ms;

	ms = tms_init();
	//ms.cmd = tcmd_init(&ms);

	//ms.line = ft_strdup("echo \"$PATH  uuu\" 'aaa   aaa' bbb \"'123  456'\" | ec\"$c$o\" \"-la\" azaza < g >> t > g");
	//ms.line = ft_strdup("echo '$PATH     uuu'");
	ms.line = ft_strdup("echo aa > a");
	tms_lineparse(&ms);
	
	
	tcmd_print(ms.cmd);

	exit(EXIT_SUCCESS);
	return (0);
}
*/