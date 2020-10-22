/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 00:39:43 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:32:56 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			tcmd_put_arg_to_name(t_ms *ms)
{
	t_cmd *ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->prev && tcmd_isempty(ptr->prev) && !tcmd_isempty(ptr) && \
			!ptr->name && ptr->arg && *ptr->arg)
		{
			ptr->name = e_strdup(*ptr->arg);
			ptr->arg = charxx_delete_one(ptr->arg, 0);
		}
		ptr = ptr->next;
	}
}

void			tcmd_move_pipes(t_ms *ms)
{
	int		i;
	t_cmd	*ptr;
	t_cmd	*ptr_cur;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->pipe && (!ptr->name || (ptr->name && in_set(*ptr->name, SET))))
		{
			ptr_cur = ptr;
			while (ptr_cur->prev && !tcmd_isempty(ptr_cur->prev) && \
				(!ptr_cur->name || (ptr_cur->name &&
				in_set(*ptr_cur->name, SET))))
				ptr_cur = ptr_cur->prev;
			if (!in_set(*ptr_cur->name, SET))
			{
				ptr->pipe = 0;
				ptr_cur->pipe = 1;
			}
		}
		ptr = ptr->next;
	}
}

static t_cmd	*tcmd_make_cmd(t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	cmd->name = e_strdup(cmd->arg[i++]);
	while (cmd->arg[i] && is_flag(cmd->arg[i]))
	{
		cmd->flag = charxx_insert(cmd->flag, cmd->arg[i], i - 1);
		i++;
	}
	j = 0;
	while (cmd->arg[i])
	{
		free(cmd->arg[j]);
		cmd->arg[j++] = e_strdup(cmd->arg[i]);
		free(cmd->arg[i]);
		cmd->arg[i++] = NULL;
	}
	while (j < i)
	{
		free(cmd->arg[j]);
		cmd->arg[j++] = NULL;
	}
	return (cmd);
}

void			tcmd_divide_args(t_ms *ms)
{
	int		i;
	t_cmd	*ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && in_set(*ptr->name, SET) &&
		ptr->arg && charxx_len(ptr->arg) > 1)
		{
			ptr = tcmd_insert(ptr);
			ptr->pipe = ptr->prev->pipe;
			ptr->prev->pipe = 0;
			i = 1;
			while (ptr->prev->arg[i])
			{
				ptr->arg = charxx_insert(ptr->arg, ptr->prev->arg[i], i - 1);
				free(ptr->prev->arg[i]);
				ptr->prev->arg[i] = NULL;
				i++;
			}
			if (!tcmd_has_cmd(ptr->prev))
				ptr = tcmd_make_cmd(ptr);
		}
		ptr = ptr->next;
	}
}

void			tcmd_flags_to_args(t_ms *ms)
{
	int		i;
	t_cmd	*ptr;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && in_set(*ptr->name, SET) && ptr->flag)
		{
			i = 0;
			while (ptr->flag[i])
			{
				ptr->arg = charxx_insert(ptr->arg, ptr->flag[i], i);
				free(ptr->flag[i]);
				ptr->flag[i] = NULL;
				i++;
			}
		}
		ptr = ptr->next;
	}
}
