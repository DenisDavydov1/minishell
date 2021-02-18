/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:59:37 by odhazzar          #+#    #+#             */
/*   Updated: 2021/02/18 23:41:40 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_write(t_ms *ms)
{
	char **arg;

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

	flag = ms->cmd->flag;
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
