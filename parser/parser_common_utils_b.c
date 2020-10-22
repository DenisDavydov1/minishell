/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_common_utils_b.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:44:53 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:27:09 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*tcmd_gotolast(t_cmd *cmd, char *s)
{
	cmd = tcmd_gotoempty(cmd);
	while (cmd)
	{
		if (!cmd->name && cmd->prev)
			cmd = cmd->prev;
		else if (cmd->name && ft_strcmp(cmd->name, s) && cmd->prev)
			cmd = cmd->prev;
		else
			break ;
	}
	return (cmd);
}

t_cmd	*tcmd_has_cmd(t_cmd *cmd)
{
	cmd = tcmd_gotocmdbegin(cmd);
	while (cmd && cmd->next && ((!cmd->name && cmd->arg) ||
	(cmd->name && in_set(*cmd->name, SET))))
		cmd = cmd->next;
	if (cmd->name && !in_set(*cmd->name, SET))
		return (cmd);
	else
		return (0);
}

t_cmd	*tcmd_get_cmd(t_cmd *cmd)
{
	while (cmd && cmd->prev && !tcmd_isempty(cmd->prev))
	{
		cmd = cmd->prev;
	}
	return (cmd);
}
