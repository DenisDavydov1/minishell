/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:34:26 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/22 08:55:24 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tenv_len(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	charxx_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	*find_in_env(t_ms *ms, char *s)
{
	t_env *tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int		find_and_replace_env(t_ms *ms, char *name, char *value)
{
	t_env	*tmp;
	char	*old_value;

	tmp = ms->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			old_value = tmp->value;
			tmp->value = value;
			free(old_value);
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
