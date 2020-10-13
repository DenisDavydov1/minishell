#include "minishell.h"

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

char **tenv_tocharxx(t_env *env)
{
    char **out;
    char **ptr;
    int len;

    out = charxx_alloc(tenv_len(env));
    ptr = out;
    while (env)
    {
        *ptr = (char *)e_calloc((ft_strlen(env->name) + \
			ft_strlen(env->value) + 4), sizeof(char));
        ft_strlcat(*ptr, env->name, (len = ft_strlen(env->name) + 1));
        ft_strlcat(*ptr, "=\"", (len += 3));
        ft_strlcat(*ptr, env->value, (len += ft_strlen(env->value) + 1));
        ft_strlcat(*ptr, "\"", (len += 2));
        ptr++;
        env = env->next;
    }
    return (out);
}

char **tenv_to_envp(t_env *env)
{
    char **envp;
    char **ptr;
    int len;

    envp = charxx_alloc(tenv_len(env));
    ptr = envp;
    while (env)
    {
        *ptr = (char *)e_calloc((ft_strlen(env->name) + \
			ft_strlen(env->value) + 1), sizeof(char));
        ft_strlcat(*ptr, env->name, (len = ft_strlen(env->name) + 1));
        ft_strlcat(*ptr, "=", (len += 2));
        ft_strlcat(*ptr, env->value, (len += ft_strlen(env->value) + 1));
        ptr++;
        env = env->next;
    }
    return (envp);
}

void ft_export_sort(t_env *env)
{
    int i;
	char **char_env;
    char **ptr;

    char_env = tenv_tocharxx(env);
	i = tenv_len(env);
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
    export_print(char_env);
	charxx_free(char_env);
}