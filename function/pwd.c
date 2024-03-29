/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:42:38 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:43:00 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_ms *ms)
{
	char *s;

	s = find_in_env(ms, "PWD");
	write(ms->cmd->fd, s, ft_strlen(s));
	write(ms->cmd->fd, "\n", 1);
	ms->ret = 0;
	return (1);
}
