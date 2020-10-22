/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tcmd_utils_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:24:02 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:40:07 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tcmd_free(t_ms *ms)
{
	t_cmd *ptr;

	if (!ms->cmd)
		return ;
	ms->cmd = tcmd_gotofirst(ms->cmd);
	while (ms->cmd)
	{
		free(ms->cmd->name);
		free(ms->cmd->file);
		charxx_free(ms->cmd->flag);
		charxx_free(ms->cmd->arg);
		ptr = ms->cmd;
		ms->cmd = ms->cmd->next;
		free(ptr);
	}
	ms->cmd = NULL;
}

void	tcmd_free_one(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->name);
	free(cmd->file);
	charxx_free(cmd->flag);
	charxx_free(cmd->arg);
	free(cmd);
}

char	**tcmd_skip(char **s)
{
	if (*s && **s == ' ')
	{
		while (*s && **s == ' ')
			s++;
	}
	return (s);
}

void	tcmd_newtcmd(t_ms *ms)
{
	if (ms->cmd->name || ms->cmd->flag || ms->cmd->arg)
		ms->cmd = tcmd_init(ms);
}

int		tcmd_set(t_ms *ms, char **s)
{
	while (*s)
	{
		if (!(s = tcmd_semicolon(ms, s)))
			return (0);
		s = tcmd_set_name(ms, s);
		ms->cmd->flag = charxx_alloc(split_countflags(s));
		while ((s = tcmd_skip(s)) && *s && is_flag(*s))
			s = tcmd_addflag(ms, s);
		ms->cmd->arg = charxx_alloc(split_countargs(s));
		while ((s = tcmd_skip(s)) && *s)
		{
			if (!in_set(**s, SET))
				s = tcmd_addarg(ms, s);
			else
				break ;
		}
		s = tcmd_pipe(ms, s);
	}
	return (1);
}
