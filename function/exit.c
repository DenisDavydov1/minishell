#include "minishell.h"

static int count_args(char **arg)
{
	int i;

	i = 0;
	if (arg && *arg)
	{
		while (*arg)
		{
			i++;
			arg++;
		}
	}
	return (i);
}

int check_arg(char *s)
{
	while (*s)
	{
		if (ft_isdigit(*s))
			s++;
		else
			return (0);
	}
	return (1);
}

int msh_exit(t_ms *ms)
{
	char **tmp;

	tmp = ms->cmd->arg;
	ms->ret = 0;
	ft_putendl_fd("exit", 1); //нужен ли fd?
	if (tmp && *tmp)
	{
		if (!check_arg(*tmp))
		{
			ft_error(ms->cmd->name, *tmp, "numeric argument required", ms);
			exit(255);
		}
		else
		{
			if (count_args(tmp) > 1)
				return (ft_error(ms->cmd->name, NULL, "too many arguments", ms));
			else 
				exit(ft_atoi(*tmp));
		}
	}
	exit(0);
}