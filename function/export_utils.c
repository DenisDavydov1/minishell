#include "minishell.h"

void env_error(char *name, char *arg, t_ms *ms)
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

void export_print(char **s)
{
	while (*s)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(*s, 1);
		s++;
	}
}

void charxx_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int tenv_len(t_env *env)
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

int check_env_name(t_ms *ms, char *s)
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
					//ft_putstr_fd("not a valid identifier\n", 1); // написать нормальную ошибку
					return (0);
				}
			}
			return (1);
		}
		//env_error(ms->cmd->name, s);
	}
	env_error(ms->cmd->name, s, ms);
	return (0);
}

int check_env_value(t_ms *ms, char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i]) //добавить обработку экранирования и кавычек
		{
			if (s[i] == ' ' || s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == '&')
			{
				env_error(ms->cmd->name, s, ms);
				//ft_putstr_fd("not a valid identifier\n", 1);
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

char		**ft_split_first(t_ms *ms, char *s, char c)
{
	char	**out;
	int i;

	i = 0;
	out = charxx_alloc(2);
	if (s)
	{
		//if (!(ft_strchr(s, c)) || (!(ft_strcmp(s, "="))))
		//if (!(ft_strchr(s, c)))

		if (!(ft_strcmp(s, "=")))
		{
			out[0] = ft_strdup(s);
			return (out);
		}
		if (!(ft_strchr(s, c)))
		{
			check_env_name(ms, s);
			free(out);
			return (NULL);
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
		//out[0] = ft_strdup(s);
		//return (out);
	}
	charxx_free(out);
	return (NULL);
}

int add_in_env(t_ms *ms, char *s) 
{
	char **test;
	t_env *tmp;
	char **value;
	char *old_value;

	//test = e_split(s, '='); //переписать функцию, делить только по первому знаку "=" ?
	test = ft_split_first(ms, s, '=');
	if (!test)
		return (0);
	//printf("test0 = |%s|  test1 = |%s| \n", test[0], test[1]);
	if ((!(check_env_name(ms, test[0]))) && (!(check_env_value(ms, test[1]))))
	//if ((!(check_env_name(ms, test[0]))))
	{
		//ms->ret = 1;
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
	free(test); //как правильно очистить?
	return (1);
}