#include "minishell_p.h"















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
		printf("Addr: %p\n", cmd);
		//printf("Prev: %p, Next: %p\n",	cmd->prev ? cmd->prev : 0, \
		//								cmd->next ? cmd->next : 0);
		printf("Prev: %s, Next: %s\n",	cmd->prev ? "Yes" : "No", \
										cmd->next ? "Yes" : "No");
		cmd = cmd->next;
	}
}
/*
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
}*/
































/*
t_cmd *tcmd_write_empty_file(t_ms *ms, t_cmd *ptr)
{
	ptr->write = 1;
	ptr = tcmd_insert(ptr);
	return (ptr->next);
}
*/
























/*
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
}*/


/*
t_cmd *tcmd_opt_greater(t_ms *ms, t_cmd *ptr)
{
	t_cmd *tmp;
	t_cmd *tmp_cmd;
	t_cmd *next;

	if (!ptr->prev || (ptr->prev && tcmd_isempty(ptr->prev)))
		return ((ptr = tcmd_insert(ptr)));
	else
	{
		next = ptr->next;
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
	}
	return (next);
}*/





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











/*
** SPLIT_SET
*/


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



/*
int get_quote_end(char *s, char quote, int start)
{
	int end;

	end = start + 1;
	while (s && s[end] && s[end] != quote)
	{
		if (is_esc_char(s, end))
			end += 2;
		else
			end++;
	}
	if (s[end] == quote)
	{
		//while (s[end + 1] && !in_set(s[end + 1], SET))
			//end++;
		return (end);
	}
	else
		return (0);
}
*/
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






/*
**
*/
/*
t_cmd *avav(t_ms *ms, t_cmd *ptr)
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

void arar(t_ms *ms)
{
	t_cmd *c;

	//c = ms->cmd->next;
	c = tcmd_gotofirst(ms->cmd);
	while (c)
	{
		if (c->name && !ft_strcmp(c->name, "<"))
		{
			c = avav(ms, c);
		}
		else
			c = c->next;
	}
}

void afaf(t_ms *ms)
{
	arar(ms);
	//tcmd_optimize_signs(ms);
}
*/


/*
int main(int argc, char **argv, char **env)
{
	t_ms ms;

	ms = tms_init();
	//ms.cmd = tcmd_init(&ms);

	//ms.line = ft_strdup("echo \"$PATH  uuu\" 'aaa   aaa' bbb \"'123  456'\" | ec\"$c$o\" \"-la\" azaza < g >> t > g");
	//ms.line = ft_strdup("echo '$PATH     uuu'");
	//ms.line = ft_strdup("ls asdf > sdf < f > er >> strt | cat sdf -e | cat -e | cat -e; sdf -n -pp sdf");
	//ms.line = ft_strdup("ls asdf > sdf > er >> strt | cat sdf -e | cat -e | cat -e");
	ms.line = ft_strdup("echo 15 > b < b");
	tms_lineparse(&ms);
	
	tcmd_print(ms.cmd);
	tcmd_free(&ms);
	free(ms.line);

	exit(EXIT_SUCCESS);
	return (0);
}
*/