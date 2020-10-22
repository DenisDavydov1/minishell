/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:03:20 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:35:15 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ignore_command(t_cmd *cmd)
{
	if (cmd->name && (!ft_strcmp(cmd->name, "echo") || \
		!ft_strcmp(cmd->name, "cd") || \
		!ft_strcmp(cmd->name, "pwd") || \
		!ft_strcmp(cmd->name, "export") || \
		!ft_strcmp(cmd->name, "unset") || \
		!ft_strcmp(cmd->name, "env") || \
		!ft_strcmp(cmd->name, "exit")))
		return (1);
	return (0);
}

static t_cmd	*tcmd_opt_less(t_ms *ms, t_cmd *ptr)
{
	t_cmd *ptr_cmd;
	t_cmd *ptr_last;
	t_cmd *next;

	if (!ptr)
		return (NULL);
	next = ptr->next;
	if ((ptr_cmd = tcmd_has_cmd(ptr)) && (!ptr_cmd->arg ||
	(ptr_cmd->arg && !*ptr_cmd->arg)))
	{
		if (!ignore_command(ptr_cmd))
		{
			ptr_last = tcmd_gotolast(ptr, "<");
			ptr_cmd->arg = charxx_insert(ptr_cmd->arg, *ptr_last->arg, 0);
			ptr_last = tcmd_delete_cmd(ms, ptr_last);
			return (next ? next : ptr);
		}
	}
	return (ptr->next);
}

static t_cmd	*tcmd_opt_greater(t_ms *ms, t_cmd *ptr)
{
	t_cmd *p_cmd;
	t_cmd *p;
	t_cmd *next;

	if (!ptr)
		return (NULL);
	next = ptr->next;
	if ((p_cmd = tcmd_has_cmd(ptr)) && p_cmd->write == 0 && !p_cmd->file)
	{
		p = tcmd_gotoempty(ptr);
		p = p->name ? p : p->prev;
		while (p && p->name && p->prev && p->prev->name && *p->name != '>')
			p = p->prev;
		p_cmd->write = *(p->name + 1) == '>' ? 2 : 1;
		p_cmd->file = e_strdup(*p->arg);
		p = tcmd_delete_cmd(ms, p);
	}
	return (ptr ? ptr->next : next);
}

void			tcmd_optimize_signs(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr && ptr->name && !ft_strcmp(ptr->name, "<"))
			ptr = tcmd_opt_less(ms, ptr);
		else if (ptr && ptr->name && (!ft_strcmp(ptr->name, ">") ||
		!ft_strcmp(ptr->name, ">>")))
			ptr = tcmd_opt_greater(ms, ptr);
		else
			ptr = ptr->next;
	}
}
