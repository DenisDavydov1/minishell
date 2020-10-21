/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tcmd_utils_a.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:16:28 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:44 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *tcmd_gotofirst(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->prev)
	{
		cmd = cmd->prev;
	}
	return (cmd);
}

static void tcmd_set_values(t_cmd **cmd)
{
	(*cmd)->name = NULL;
	(*cmd)->flag = NULL;
	(*cmd)->arg = NULL;
	(*cmd)->pipe = 0;
	(*cmd)->write = 0;
	(*cmd)->fd = 1;
	(*cmd)->file = NULL;
	(*cmd)->pfd[0] = 0;
	(*cmd)->pfd[1] = 1;
	(*cmd)->next = NULL;
}

t_cmd *tcmd_init(t_ms *ms)
{
	t_cmd *cmd;

	cmd = (t_cmd *)e_malloc(sizeof(t_cmd));
	tcmd_set_values(&cmd);
	cmd->prev = ms->cmd;
	if (ms->cmd)
		ms->cmd->next = cmd;
	return (cmd);
}


t_cmd *tcmd_insert(t_cmd *to)
{
	t_cmd *cmd;
	t_cmd *t;

	cmd = (t_cmd *)e_malloc(sizeof(t_cmd));
	tcmd_set_values(&cmd);
	cmd->prev = NULL;
	if (to->next)
	{
		t = to->next;
		to->next = cmd;
		cmd->next = t;
		t->prev = cmd;
		cmd->prev = to;	
	}
	else
	{
		to->next = cmd;
		cmd->prev = to;
	}
	return (cmd);
}

t_ms tms_init(void)
{
	t_ms ms;

	ms.line = NULL;
	ms.path = NULL;
	ms.cmd = NULL;
	ms.env = NULL;
	ms.ret = 0;
	return (ms);
}