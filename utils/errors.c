/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:46:56 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:48:17 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *name, char *arg, char *error, t_ms *ms)
{
	ft_putstr_fd("minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	ms->ret = 1;
	return (0);
}

int	throw_error(char *errtype, t_ms *ms)
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
		else if (!ft_strcmp(errtype, ISADIRERR) ||
				!ft_strcmp(errtype, PERMISSIONERR))
			exit(126);
	}
	return (1);
}
