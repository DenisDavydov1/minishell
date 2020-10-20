#include "minishell.h"

/*int throw_error(char *errtype, t_ms *ms)
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
		ms->ret = 258;
	}
	else if (!ft_strcmp(errtype, CMDNFERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(CMDNFERR, 2);
		//ms->ret = 127;
		//exit(EXIT_FAILURE);
		exit(127);
	}
	else if (!ft_strcmp(errtype, CDERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(CDERR, 2);
		//ms->ret = 127;
		exit(127);
	}
	else if (!ft_strcmp(errtype, ISADIRERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(ISADIRERR, 2);
		//ms->ret = 126;
		exit(126);
	}
	else if (!ft_strcmp(errtype, PERMISSIONERR))
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(PERMISSIONERR, 2);
		exit(126);
	}
	return (1);
}*/

int throw_error(char *errtype, t_ms *ms)
{
	ft_putstr_fd("minishell: ", 2);
	if (!ft_strcmp(errtype, MEMALLOC) || !ft_strcmp(errtype, PIPEERR))
	{
		ft_putendl_fd(errtype, 2);
		exit(EXIT_FAILURE);
	}
	else if (!ft_strcmp(errtype, PARSEERR))
	{
		ft_putendl_fd(PARSEERR, 2);
		tcmd_free(ms);
		ms->ret = 258;
	}
	else
	{
		ft_putstr_fd(ms->cmd->name, 2);
		ft_putendl_fd(errtype, 2);
		if (!ft_strcmp(errtype, CMDNFERR) || !ft_strcmp(errtype, CDERR))
			exit(127);
		else if (!ft_strcmp(errtype, ISADIRERR) || !ft_strcmp(errtype, PERMISSIONERR))
			exit(126);
	}
	return (0);
}

