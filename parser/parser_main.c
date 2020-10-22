/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 01:24:56 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:29:26 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tms_lineparse(t_ms *ms)
{
	char **split;

	if (!(split = e_splitset(ms->line, SET)) && throw_error(PARSEERR, ms))
		return (0);
	if (!split_validity(split) && throw_error(PARSEERR, ms))
		return (0);
	ms->cmd = ms->cmd ? ms->cmd : tcmd_init(ms);
	if (!tcmd_set(ms, split))
	{
		charxx_free(split);
		return (0);
	}
	charxx_free(split);
	tcmd_optimize(ms);
	return (1);
}
