/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:14:17 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/22 08:56:23 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(char **s, t_ms *ms)
{
	while (*s)
	{
		ft_putstr_fd("declare -x ", ms->cmd->fd);
		ft_putendl_fd(*s, ms->cmd->fd);
		s++;
	}
}

char		**tenv_tocharxx(t_env *env)
{
	char	**out;
	char	**ptr;
	int		len;

	out = charxx_alloc(tenv_len(env));
	ptr = out;
	while (env)
	{
		*ptr = (char *)e_calloc((ft_strlen(env->name) + \
			ft_strlen(env->value) + 4), sizeof(char));
		ft_strlcat(*ptr, env->name, (len = ft_strlen(env->name) + 1));
		if (env->value)
		{
			ft_strlcat(*ptr, "=\"", (len += 3));
			ft_strlcat(*ptr, env->value, (len += ft_strlen(env->value) + 1));
			ft_strlcat(*ptr, "\"", (len += 2));
		}
		ptr++;
		env = env->next;
	}
	return (out);
}

char		**tenv_to_envp(t_env *env)
{
	char	**envp;
	char	**ptr;
	int		len;

	envp = charxx_alloc(tenv_len(env));
	ptr = envp;
	while (env)
	{
		*ptr = (char *)e_calloc((ft_strlen(env->name) + \
			ft_strlen(env->value) + 2), sizeof(char));
		ft_strlcat(*ptr, env->name, (len = ft_strlen(env->name) + 1));
		ft_strlcat(*ptr, "=", (len += 2));
		ft_strlcat(*ptr, env->value, (len += ft_strlen(env->value) + 1));
		ptr++;
		env = env->next;
	}
	return (envp);
}

static void	ft_export_sort(t_ms *ms)
{
	int		i;
	char	**char_env;
	char	**ptr;

	char_env = tenv_tocharxx(ms->env);
	i = tenv_len(ms->env);
	while (i)
	{
		ptr = char_env;
		while (*(ptr + 1))
		{
			if (ft_strcmp(*ptr, *(ptr + 1)) > 0)
				charxx_swap(ptr, ptr + 1);
			ptr++;
		}
		i--;
	}
	export_print(char_env, ms);
	charxx_free(char_env);
	ms->ret = 0;
}

int			msh_export(t_ms *ms)
{
	char **tmp;

	ms->ret = 0;
	tmp = ms->cmd->arg;
	if (tmp && *tmp)
	{
		while (*tmp)
		{
			add_in_env(ms, *tmp);
			tmp++;
		}
	}
	else
		ft_export_sort(ms);
	return (1);
}
