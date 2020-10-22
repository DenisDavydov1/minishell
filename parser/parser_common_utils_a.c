/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_common_utils_a.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:43:13 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:25:50 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		in_set(char c, char *set)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

int		is_flag(char *s)
{
	if (*s == '\"' || *s == '\'')
		s++;
	if ((*s == '-' && ft_strlen(s) > 1 && !ft_strchr(s + 1, '-')) || \
		(*s == '-' && ft_strlen(s) > 2 && *(s + 1) == '-' &&
		!ft_strchr(s + 2, '-')))
		return (1);
	return (0);
}

int		tcmd_isempty(t_cmd *cmd)
{
	if (cmd->name || (cmd->flag && *cmd->flag) || (cmd->arg && *cmd->arg))
		return (0);
	return (1);
}

t_cmd	*tcmd_gotoempty(t_cmd *cmd)
{
	while (cmd && !tcmd_isempty(cmd) && cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

t_cmd	*tcmd_gotocmdbegin(t_cmd *cmd)
{
	while (cmd && cmd->prev && !tcmd_isempty(cmd->prev))
	{
		cmd = cmd->prev;
	}
	return (cmd);
}
