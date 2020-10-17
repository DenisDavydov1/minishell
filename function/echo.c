#include "minishell.h"

void echo_write(t_ms *ms)
{
	char **arg;
	char *s;

	s = NULL;
	arg = ms->cmd->arg;
	if (arg && *arg)
	{
		while (*arg)
		{
			if (**arg == '$')
			{
				if (ft_strlen(*arg) > 1)
				{
					s = find_in_env(ms, *arg + 1);
					if (s)
						write(ms->cmd->fd, s, ft_strlen(s));
				}
				else
					write(ms->cmd->fd, "$", 1);
			}
			else
				write(ms->cmd->fd, *arg, ft_strlen(*arg));
			arg++;
			if (*arg)
				write(ms->cmd->fd, " ", 1);
		}
	}
}

int msh_echo(t_ms *ms)
{
	char **flag;
	char **arg;

	flag = ms->cmd->flag;
	arg = ms->cmd->arg;
	if (flag && *flag && ft_strcmp1(*flag, "-n"))
		echo_write(ms);
	else
	{
		echo_write(ms);
		write(ms->cmd->fd, "\n", 1);
	}
	return (1);
}