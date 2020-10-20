#include "minishell.h"

void delete_from_env(t_ms *ms, char *s)
{
	t_env *tmp;
	t_env *prev;

	tmp = ms->env;
	prev = tmp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s))
		{
			if (prev == tmp)
				ms->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int msh_unset(t_ms *ms)
{
	char **tmp;

	ms->ret = 0;
	tmp = ms->cmd->arg;
	if (tmp && *tmp)
	{
		while (*tmp)
		{
			if (check_env_name(ms, *tmp))
				delete_from_env(ms, *tmp);
			tmp++;
		}
	}
	return (1);
}