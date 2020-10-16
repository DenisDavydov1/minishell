#include "minishell.h"

int throw_error(char *errtype, t_ms *ms)
{
	ft_putstr_fd("minishell: ", 2);
	if (!ft_strcmp(errtype, MEMALLOC))
	{
		ft_putendl_fd(errtype, 2);
		exit(EXIT_FAILURE);
	}	
	else if (!ft_strcmp(errtype, PARSEERR))
	{
		ft_putendl_fd(PARSEERR, 2);
		tcmd_free(ms);
	}
	else if (!ft_strcmp(errtype, CMDNFERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(CMDNFERR, 2);
		exit(EXIT_FAILURE);
	}
	else if (!ft_strcmp(errtype, CDERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(CDERR, 2);
		exit(EXIT_FAILURE);
	}
	else if (!ft_strcmp(errtype, ISADIRERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(ISADIRERR, 2);
		exit(EXIT_FAILURE);
	}
	return (1);
}
