/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:59:37 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:10:41 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_write(t_ms *ms)
{
	char **arg;
	char *s;

	s = NULL;
	arg = ms->cmd->arg;
	if (arg && *arg)
	{
		while (*arg)
		{
			write(ms->cmd->fd, *arg, ft_strlen(*arg));
			arg++;
			if (*arg)
				write(ms->cmd->fd, " ", 1);
		}
	}
}

int			msh_echo(t_ms *ms)
{
	char **flag;
	char **arg;

	flag = ms->cmd->flag;
	arg = ms->cmd->arg;
	if (flag && *flag && (!ft_strcmp(*flag, "-n")))
		echo_write(ms);
	else
	{
		echo_write(ms);
		write(ms->cmd->fd, "\n", 1);
	}
	ms->ret = 0;
	return (1);
}
