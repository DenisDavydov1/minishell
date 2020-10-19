#include "minishell.h"

int msh_env(t_ms *ms)
{
	t_env *tmp;

	tmp = ms->env;
	while (tmp && tmp->name)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	ms->ret = 0;
	return (1);
}