/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:06:46 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:34 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void tcmd_remove_signs(t_ms *ms)
{
	t_cmd *p;

	p = tcmd_gotofirst(ms->cmd);
	while (p)
	{
		if (p->name && in_set(*p->name, SET))
			p = tcmd_delete_cmd(ms, p);
		else
			p = p->next;
	}
}

static t_cmd *patc(t_ms *ms, t_cmd *ptr)
{
	int i;
	t_cmd *ptr_cmd;
	t_cmd *ptr_last;

	ptr_cmd = ptr;
	ptr_last = tcmd_gotoempty(ptr);
	while (ptr)
	{
		if (!ptr->name && ptr->arg)
		{
			i = -1;
			while (ptr->arg[++i])
			{
				ptr_cmd->arg = charxx_insert(ptr_cmd->arg, ptr->arg[i], \
					charxx_len(ptr_cmd->arg));
				free(ptr->arg[i]);
				ptr->arg[i] = NULL;
			}
			ptr = tcmd_delete_cmd(ms, ptr);
		}
		if (ptr == ptr_last)
			break ;
		ptr = ptr ? ptr->next : ptr;
	}
	return (ptr);
}


void tcmd_put_args_to_cmd(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (tcmd_isempty(ptr) || (ptr->name && in_set(*ptr->name, SET)))
		{
			ptr = ptr->next;
			continue ;
		}
		ptr = patc(ms, ptr);
		ptr = ptr ? ptr->next : ptr;
	}
}