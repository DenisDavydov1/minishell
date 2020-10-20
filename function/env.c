#include "minishell.h"

int msh_env(t_ms *ms)
{
	t_env *tmp;

	tmp = ms->env;
	while (tmp && tmp->name)
	{
		if (tmp->value)
		{
			write(ms->cmd->fd, tmp->name, ft_strlen(tmp->name));
			write(ms->cmd->fd, "=", 1);
			write(ms->cmd->fd, tmp->value, ft_strlen(tmp->value));
			write(ms->cmd->fd, "\n", 1);
		}
		tmp = tmp->next;
	}
	ms->ret = 0;
	return (1);
}