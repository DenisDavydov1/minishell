#include "minishell.h"

void *emalloc(size_t size)
{
	void *out;
	
	if (!(out = malloc(size)))
		exit(EXIT_FAILURE);
	return (out);
}

t_cmd *tcmdgotofirst(t_cmd *cmd)
{
	while (cmd->prev)
	{
		cmd = cmd->prev;
	}
	return (cmd);
}

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

void tcmdfree(t_cmd *cmd)
{
	t_cmd *ptr;
	int i;

	if (!cmd)
		return ;
	cmd = tcmdgotofirst(cmd);
	while (cmd)
	{
		charxxfree(cmd->flag);
		charxxfree(cmd->arg);
		ptr = cmd;
		cmd = cmd->next;
		free(ptr);
	}
}

void tmsfree(t_ms *ms)
{
	if (!ms)
		return ;
	//free(ms->line);
	//free(ms->path);
	tcmdfree(ms->cmd);
}

void throw_error(char *errtype, t_ms *ms)
{
	tmsfree(ms);
	ft_putendl_fd(errtype, 2);
	exit(EXIT_FAILURE);
}

t_cmd *tcmdinit(t_ms *ms)
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

t_ms tmsinit(void)
{
	t_ms ms;

	ms.line = NULL;
	ms.path = NULL;
	ms.env = NULL;
	ms.cmd = tcmdinit(&ms);
	
	return (ms);
}


void cmd_line_parse(t_ms *ms)
{

}

int main(int argc, char **argv, char **env)
{
	t_ms ms;

	ms = tmsinit();
	ms.line = "cat parcer.c < parcer.c";
	ms.cmd->next = tcmdinit(&ms);
	tmsfree(&ms);
	//

	//free(ms.cmd);
	//exit(EXIT_SUCCESS);
	return (0);
}
