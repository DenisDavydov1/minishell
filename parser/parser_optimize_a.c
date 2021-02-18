/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_optimize_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 00:39:40 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:31:04 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tcmd_set_echo_err_a(t_ms *ms, t_cmd *p)
{
	t_cmd	*p_cmd;
	int		pipe;

	p_cmd = tcmd_get_cmd(p);
	while (p_cmd && p_cmd)
	{
		if (p_cmd->pipe == 1)
			pipe = 1;
		if (p_cmd == p)
			p_cmd = p_cmd->next;
		else
			p_cmd = tcmd_delete_cmd(ms, p_cmd);
		if (!p_cmd || (tcmd_isempty(p_cmd) && pipe == 0))
			break ;
		else if (tcmd_isempty(p_cmd) && pipe == 1 && !(pipe = 0))
			p_cmd = p_cmd->next;
	}
}

static void	tcmd_set_echo_err(t_ms *ms, t_cmd *p, char *errtype)
{
	int		len;

	p = tcmd_insert(p);
	p->write = -1;
	p->name = e_strdup("echo");
	p->arg = charxx_alloc(2);
	*p->arg = e_calloc(12 + ft_strlen(*p->prev->arg) +
	ft_strlen(errtype), sizeof(char));
	ft_strlcat(*p->arg, "minishell: ", (len = ft_strlen("minishell: ") + 1));
	ft_strlcat(*p->arg, *p->prev->arg, (len += ft_strlen(*p->prev->arg) + 1));
	ft_strlcat(*p->arg, errtype, (len += ft_strlen(errtype) + 1));
	tcmd_set_echo_err_a(ms, p);
}

static void	open_close(t_ms *ms, t_cmd *ptr, int fd)
{
	if (fd < 0)
		tcmd_set_echo_err(ms, ptr, CDERR);
	else
		close(fd);
}

static void	tcmd_open_create_files(t_ms *ms)
{
	t_cmd	*ptr;
	int		fd;

	ptr = tcmd_gotofirst(ms->cmd);
	while (ptr)
	{
		if (ptr->name && !ft_strcmp(ptr->name, "<") && ptr->arg && *ptr->arg)
		{
			*ptr->arg = parse_quotes(*ptr->arg, ms);
			ptr->prsd = 1;
			fd = open(*ptr->arg, O_RDONLY);
			open_close(ms, ptr, fd);
		}
		else if (ptr->name && (!ft_strcmp(ptr->name, ">") || \
			!ft_strcmp(ptr->name, ">>") || !ft_strcmp(ptr->name, "<>")) && \
			ptr->arg && *ptr->arg)
		{
			*ptr->arg = parse_quotes(*ptr->arg, ms);
			ptr->prsd = 2;
			fd = open(*ptr->arg, O_CREAT, 0644);
			open_close(ms, ptr, fd);
		}
		ptr = ptr->next;
	}
}

void		tcmd_optimize(t_ms *ms)
{
	if (!ms->cmd)
		return ;
	tcmd_divide_args(ms);
	tcmd_move_pipes(ms);
	tcmd_flags_to_args(ms);
	tcmd_put_arg_to_name(ms);
	tcmd_put_args_to_cmd(ms);
	tcmd_open_create_files(ms);
	tcmd_replace_lg(ms);
	tcmd_optimize_signs(ms);
	tcmd_remove_nulls(ms);
	tcmd_remove_signs(ms);
	ms->cmd = tcmd_gotofirst(ms->cmd);
}
