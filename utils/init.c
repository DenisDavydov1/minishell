/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:50:06 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:50:51 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*tenv_init(char *name, char *value)
{
	t_env *env;

	env = (t_env *)e_malloc(sizeof(t_env));
	if (!(ft_strcmp(name, "OLDPWD")))
	{
		env->name = e_strdup(name);
		env->value = NULL;
		env->next = NULL;
	}
	else
	{
		env->name = e_strdup(name);
		env->value = e_strdup(value);
		env->next = NULL;
	}
	return (env);
}

void	tenv_set(t_ms *ms, char **envp)
{
	t_env	*e;
	char	**split;

	e = NULL;
	while (*envp)
	{
		split = e_split(*envp, '=');
		if (!e)
		{
			ms->env = tenv_init(split[0], split[1]);
			e = ms->env;
		}
		else
		{
			e->next = tenv_init(split[0], split[1]);
			e = e->next;
		}
		charxx_free(split);
		envp++;
	}
	ms->path = e_split(find_in_env(ms, "PATH"), ':');
}
