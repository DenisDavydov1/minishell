/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:34:26 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:47:24 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
