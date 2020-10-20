#include "minishell.h"

t_env *tenv_init(char *name, char *value)
{
	t_env *env;

	env = (t_env *)e_malloc(sizeof(t_env));
	if (!(ft_strcmp(name, "OLDPWD")))
	{
		env->name = name;
		env->value = NULL;
		env->next = NULL;
		free(value);
	}
	else
	{
		env->name = name;
		env->value = value;
		env->next = NULL;
	}
	return (env);
}

void tenv_set(t_ms *ms, char **envp)
{
	t_env *e;
	char **split;

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
		free(split);
		envp++;
	}
	ms->path = e_split(find_in_env(ms, "PATH"), ':');
	//ms->home = ft_strdup(find_in_env(ms, "HOME"));
}

void tenv_print(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		printf("%3d. %s = %s\n", i,\
			env->name ? env->name : NULL, \
			env->value ? env->value : NULL);
		i++;
		env = env->next;
	}
}
