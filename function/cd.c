#include "minishell.h"

void replace_pwd(t_ms *ms)
{
	t_env *tmp;
	t_env *pwd;
	t_env *old_pwd;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strcmp2(tmp->name, "PWD", 3))
			pwd = tmp;
		if (ft_strcmp2(tmp->name, "OLDPWD", 6))
			old_pwd = tmp;
		tmp = tmp->next;
	}
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = NULL;
	pwd->value = getcwd(pwd->value, 0); //убрать эту функцию и передавать путь вручную (косяк с регистром)?
}

int msh_cd(t_ms *ms)
{
	char **tmp;

	tmp = ms->cmd->arg;
	if (tmp && *tmp)
	{
		if (chdir(*tmp) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(find_in_env(ms, "HOME")) != 0)
			perror("cd");
	}
	replace_pwd(ms);

	return 1;
}