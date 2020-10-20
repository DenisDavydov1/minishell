#include "minishell.h"

int msh_pwd(t_ms *ms)
{
	char *s;

	s = find_in_env(ms, "PWD");
	write(ms->cmd->fd, s, ft_strlen(s));
	write(ms->cmd->fd, "\n", 1);
	ms->ret = 0;
	return (1);
}