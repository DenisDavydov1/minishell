/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:29:43 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:55:26 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_execute(t_ms *ms)
{
	int ret;

	ret = 1;
	if (ft_strcmp_reg(ms->cmd->name, "echo"))
		return (ret = msh_echo(ms));
	else if (ft_strcmp_reg(ms->cmd->name, "cd"))
		return (ret = msh_cd(ms));
	else if (ft_strcmp_reg(ms->cmd->name, "pwd"))
		return (ret = msh_pwd(ms));
	else if (ft_strcmp_reg(ms->cmd->name, "export"))
		return (ret = msh_export(ms));
	else if (ft_strcmp_reg(ms->cmd->name, "unset"))
		return (ret = msh_unset(ms));
	else if (ft_strcmp_reg(ms->cmd->name, "env"))
		return (ret = msh_env(ms));
	else if (ft_strcmp_reg(ms->cmd->name, "exit"))
		return (ret = msh_exit(ms));
	else
		return (ret = msh_launch(ms));
}

static int	msh_loop(t_ms *ms)
{
	write(1, "minishell-1.0$ ", 15);
	ms->line = NULL;
	ms->line = get_next_line(ms->line);
	if (ms->line && *ms->line && tms_lineparse(ms))
	{
		while (ms->cmd)
		{
			tcmd_parse_quotes(ms);
			if (ms->cmd->name && *ms->cmd->name)
			{
				ms->cmd->fd = msh_set_fd(ms);
				msh_set_pfd(ms);
				msh_execute(ms);
				close_pfd(ms);
			}
			if (!ms->cmd->next)
				break ;
			ms->cmd = ms->cmd->next;
		}
	}
	free(ms->line);
	ms->line = NULL;
	tcmd_free(ms);
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	t_ms ms;

	ms = tms_init();
	tenv_set(&ms, envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (msh_loop(&ms))
		NULL;
	return (EXIT_SUCCESS);
}
