/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:48:50 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/22 09:48:45 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_error(char *name, char *arg, t_ms *ms)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd("not a valid identifier", 2);
	ms->ret = 1;
}

int		check_env_name(t_ms *ms, char *s)
{
	int i;

	i = 0;
	if (s)
	{
		if (s[i] == '_' || ft_isalpha(s[i]))
		{
			i++;
			while (s[i])
			{
				if (s[i] == '_' || ft_isalpha(s[i]) || ft_isdigit(s[i]))
					i++;
				else
				{
					env_error(ms->cmd->name, s, ms);
					return (0);
				}
			}
			return (1);
		}
	}
	env_error(ms->cmd->name, s, ms);
	return (0);
}

char	**ft_split_first(t_ms *ms, char *s, char c)
{
	char	**out;
	int		i;

	i = 0;
	out = charxx_alloc(2);
	if (s)
	{
		if ((!(ft_strcmp(s, "="))) || (!(ft_strchr(s, c))))
		{
			out[0] = ft_strdup(s);
			return (out);
		}
		while (s[i])
		{
			if (s[i] == c)
			{
				out[0] = ft_substr(s, 0, i);
				out[1] = ft_substr(s, i + 1, ft_strlen(s) - i);
				return (out);
			}
			i++;
		}
	}
	charxx_free(out);
	return (NULL);
}

int		add_in_env(t_ms *ms, char *s)
{
	char	**test;
	t_env	*tmp;
	char	**value;
	char	*old_value;

	test = ft_split_first(ms, s, '=');
	if (!test)
		return (0);
	if (!check_env_name(ms, test[0]))
	{
		charxx_free(test);
		return (0);
	}
	if (!(find_and_replace_env(ms, test[0], test[1])))
	{
		tmp = ms->env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_env *)e_malloc(sizeof(t_env));
		tmp->next->name = test[0];
		tmp->next->value = test[1];
		tmp->next->next = NULL;
	}
	free(test);
	return (1);
}
