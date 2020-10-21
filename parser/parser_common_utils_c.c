/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_common_utils_c.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:02:00 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:20 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **tcmd_set_name(t_ms *ms, char **s)
{
	s = tcmd_skip(s);
	if (*s && **s == '>' && *(s + 1) && **(s + 1) == '>')
	{
		tcmd_newtcmd(ms);
		ms->cmd->name = ft_strdup(">>");
		return (s + 2);
	}
	else if (*s && **s == '<' && *(s + 1) && **(s + 1) == '>')
	{
		tcmd_newtcmd(ms);
		ms->cmd->name = ft_strdup("<>");
		return (s + 2);
	}
	else if (*s && **s != ';' && **s != '|')
	{
		tcmd_newtcmd(ms);
		ms->cmd->name = ft_strdup(*s);
		return (s + 1);
	}
	return (s);
}

char **tcmd_addflag(t_ms *ms, char **s)
{
	int i;

	i = 0;
	while (ms->cmd->flag[i])
		i++;
	ms->cmd->flag[i] = e_strdup(*s);
	return (s + 1);
}

char **tcmd_addarg(t_ms *ms, char **s)
{
	int i;

	i = 0;
	while (ms->cmd->arg[i])
		i++;
	ms->cmd->arg[i] = e_strdup(*s);
	return (s + 1);
}

char **tcmd_semicolon(t_ms *ms, char **s)
{
	s = tcmd_skip(s);
	if (*s && **s == ';')
	{
		if (!ms->cmd->name && !ms->cmd->flag && !ms->cmd->arg && throw_error(PARSEERR, ms))
			return (NULL);
		ms->cmd = tcmd_init(ms);
		ms->cmd = tcmd_init(ms);
		return (s + 1);
	}
	return (s);
}

char **tcmd_pipe(t_ms *ms, char **s)
{
	s = tcmd_skip(s);
	if (*s && **s == '|')
	{
		ms->cmd->pipe = 1;
		ms->cmd = tcmd_init(ms);
		ms->cmd = tcmd_init(ms);
		return (s + 1);
	}
	return (s);
}