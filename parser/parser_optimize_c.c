/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:00:12 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:30 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void tcmd_remove_nulls(t_ms *ms)
{
	t_cmd *ptr;

	if (!ms->cmd)
		return ;
	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (tcmd_isempty(ptr))
			ptr = tcmd_delete_cmd(ms, ptr);
		else
			ptr = ptr->next;
	}
}

void tcmd_replace_lg(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && !ft_strcmp(ptr->name, "<>"))
		{
			free(ptr->name);
			ptr->name = e_strdup("<");
		}
		ptr = ptr->next;
	}
}

int tcmd_delete_cmd_if_equal(t_ms *ms)
{
	if (ms->cmd->next)
		ms->cmd = ms->cmd->next;
	else if (ms->cmd->prev)
		ms->cmd = ms->cmd->prev;
	else
	{
		tcmd_free(ms);
		return (1);
	}
	return (0);
}

t_cmd *tcmd_delete_cmd(t_ms *ms, t_cmd *ptr)
{
	t_cmd *next;

	if (!ms || !ptr)
		return (NULL);
	if (ms->cmd == ptr)
		if (tcmd_delete_cmd_if_equal(ms))
			return (NULL);
	if (ptr->next)
	{
		ptr->next->prev = ptr->prev;
		if (ptr->prev)
			ptr->prev->next = ptr->next;
	}	
	else if (ptr->prev)
	{
		ptr->prev->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
	}
	next = ptr->next;
	tcmd_free_one(ptr);
	return (next);
}

