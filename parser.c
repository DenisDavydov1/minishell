#include "minishell.h"

void *emalloc(size_t size)
{
	void *out;
	
	if (!(out = malloc(size)))
		exit(EXIT_FAILURE);
	return (out);
}

void tcmd_gotofirst(t_cmd **cmd)
{
	while ((*cmd)->prev)
	{
		*cmd = (*cmd)->prev;
	}
}

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

void throw_error(char *errtype, t_ms *ms)
{
	tms_free(ms);
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(errtype, 2);
	exit(EXIT_FAILURE);
}

t_cmd *tcmd_init(t_ms *ms)
{
	t_cmd *cmd;
	int i;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		throw_error(MEMALLOC, ms);
	ft_memset(cmd->name, 0, 255);
	i = 0;
	while (i < 20)
	{
		ft_memset(cmd->flag[i], 0, 100);
		ft_memset(cmd->arg[i], 0, 255);
		i++;
	}
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
	ms.cmd = tcmd_init(&ms);
	ms.env = NULL;
	return (ms);
}

void tcmd_print(t_cmd *cmd)
{
	int i = 0;
	tcmd_gotofirst(&cmd);
	while (cmd)
	{
		printf("\nCMD #%d\n", i++);
		printf("name: %s\n", cmd->name);
		printf("Flags: ");
		for (int j=0; cmd->flag[j][0]; j++)
			printf("%s ", cmd->flag[j]);
		printf("\nArgs: ");
		for (int j=0; cmd->arg[j][0]; j++)
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
	if (**s == ';')
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
		s++;
	}
	return (1);
}

char **tcmd_skip(t_ms *ms, char **s)
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
	if (*ms->cmd->name)
		ms->cmd = tcmd_init(ms);
}

char **tcmd_set_name(t_ms *ms, char **s)
{
	s = tcmd_skip(ms, s);
	if (*s && **s == '>' && *(s + 1) && **(s + 1) == '>')
	{
		ft_strcpy(ms->cmd->name, ">>");
		return (s + 2);
	}
	else if (*s && **s == '<' && *(s + 1) && **(s + 1) == '>')
	{
		ft_strcpy(ms->cmd->name, "<>");
		return (s + 2);
	}
	else if (*s && **s != ';')
	{
		ft_strcpy(ms->cmd->name, *s);
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

void tcmd_addflag(t_cmd **cmd, char *flag)
{
	int i;

	if (*flag == ' ')
		return ;
	i = 0;
	while ((*cmd)->flag[i][0])
		i++;
	ft_strcpy((*cmd)->flag[i], flag);
}

void tcmd_addarg(t_cmd **cmd, char *arg)
{
	int i;

	if (*arg == ' ')
		return ;
	i = 0;
	while ((*cmd)->arg[i][0])
		i++;
	ft_strcpy((*cmd)->arg[i], arg);
}

char **tcmd_semicolon(t_ms *ms, char **s)
{
	s = tcmd_skip(ms, s);
	if (*s && **s == ';')
	{
		ms->cmd = tcmd_init(ms);
		return (s + 1);
	}
	return (s);
}

void tcmd_set(t_ms *ms, char **s)
{
	while (*s)
	{
		s = tcmd_semicolon(ms, s);
		//if (*s && **s == ';' && (ms->cmd = tcmd_init(ms)))
		//	s++;
		//if (*s && **s != ';')
		s = tcmd_set_name(ms, s);
		while ((s = tcmd_skip(ms, s)) && *s && is_flag(*s))
		{
			//s = tcmd_skip(ms, s);
			tcmd_addflag(&ms->cmd, *s);
			s++;
		}
		while ((s = tcmd_skip(ms, s)) && *s)
		{
			//s = tcmd_skip(ms, s);
			if (!in_set(**s, SET))
			{
				tcmd_addarg(&ms->cmd, *s);
				s++;
			}
			else
				break ;
		}
	}
}

void tms_lineparse(t_ms *ms)
{
	char **split;

	if (!(split = ft_splitset(ms->line, SET)))
		throw_error(MEMALLOC, ms);
	if (!split_validity(split))
		throw_error(PARSEERR, ms); // free split array if validation fails
	// add flags and args counting and allocation char** 
	tcmd_set(ms, split);


	
	//free(split);

}

int main(int argc, char **argv, char **env)
{
	t_ms ms;

	ms = tms_init();
	ms.line = "  cat -t a; man <> a  > b; ;   yu"; // name may be <>

	tms_lineparse(&ms);

	tcmd_print(ms.cmd);
	tms_free(&ms);

	//free(ms.cmd);
	//exit(EXIT_SUCCESS);*/
	return (0);
}



/*
void charxxfree(char **s)
{
	int i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void tcmd_free(t_cmd *cmd)
{
	t_cmd *ptr;
	int i;

	if (!cmd)
		return ;
	tcmd_gotofirst(&cmd);
	while (cmd)
	{
		charxxfree(cmd->flag);
		charxxfree(cmd->arg);
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

void throw_error(char *errtype, t_ms *ms)
{
	tms_free(ms);
	ft_putendl_fd(errtype, 2);
	exit(EXIT_FAILURE);
}

t_cmd *tcmd_init(t_ms *ms)
{
	t_cmd *cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		throw_error(MEMALLOC, ms);
	cmd->name = NULL;
	cmd->flag = NULL;
	cmd->arg = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	if (!(cmd->flag = (char **)malloc(sizeof(char *))))
		throw_error(MEMALLOC, ms);
	*cmd->flag = NULL;
	if (!(cmd->arg = (char **)malloc(sizeof(char *))))
		throw_error(MEMALLOC, ms);
	*cmd->arg = NULL;
	return (cmd);
}

t_ms tms_init(void)
{
	t_ms ms;

	ms.line = NULL;
	ms.path = NULL;
	ms.env = NULL;
	ms.cmd = tcmd_init(&ms);
	
	return (ms);
}


void tcmd_addflag(t_cmd **cmd, char *flag)
{
	char **ptr;

	ptr = (*cmd)->flag;
	while (ptr)
		ptr++;
	*ptr = flag;
	++ptr = NULL;
}
*/