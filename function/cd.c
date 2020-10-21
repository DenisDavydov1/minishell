/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:57:54 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:10:20 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_pwd(t_ms *ms)
{
	t_env *tmp;
	t_env *pwd;
	t_env *old_pwd;

	tmp = ms->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
			pwd = tmp;
		if (!ft_strcmp(tmp->name, "OLDPWD"))
			old_pwd = tmp;
		tmp = tmp->next;
	}
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = NULL;
	pwd->value = getcwd(pwd->value, 0);
}

int			msh_cd(t_ms *ms)
{
	char **tmp;
	char *home;

	tmp = ms->cmd->arg;
	ms->ret = 0;
	home = find_in_env(ms, "HOME");
	if (tmp && *tmp)
	{
		if (!(ft_strcmp(*tmp, "-")))
		{
			if (chdir(find_in_env(ms, "OLDPWD")) != 0)
				return (ft_error(ms->cmd->name, NULL, "OLDPWD not set", ms));
		}
		else if (chdir(*tmp) != 0)
			return (ft_error(ms->cmd->name, *tmp, strerror(errno), ms));
	}
	else
	{
		if (!home)
			return (ft_error(ms->cmd->name, NULL, "HOME not set", ms));
		else if (chdir(home) != 0)
			return (ft_error(ms->cmd->name, *tmp, strerror(errno), ms));
	}
	replace_pwd(ms);
	return (1);
}
