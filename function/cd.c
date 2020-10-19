#include "minishell.h"

/*void check_home(t_ms *ms, char *home)
{
	if (home)
	{
		if (ft_strcmp(home, ms->home))
		{
			free(ms->home);
			ms->home = ft_strdup(home);
		}
	}
}*/

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
	char *home;

	tmp = ms->cmd->arg;
	ms->ret = 0;
	home = find_in_env(ms, "HOME");
	//check_home(ms, home);
	if (tmp && *tmp)
	{
		/*if (!(ft_strcmp(*tmp, "~")))
		{
			if (chdir(ms->home) != 0)
				ft_error(ms->cmd->name, ms->home, strerror(errno));
		}	*/
		if (!(ft_strcmp(*tmp, "-")))
		{
			if (chdir(find_in_env(ms, "OLDPWD")) != 0)
				ft_error(ms->cmd->name, NULL, "OLDPWD not set", ms);
		}
		else if (chdir(*tmp) != 0)
			ft_error(ms->cmd->name, *tmp, strerror(errno), ms);
	}
	else
	{
		if (!home)
			ft_error(ms->cmd->name, NULL, "HOME not set", ms);
		else if (chdir(home) != 0)
			ft_error(ms->cmd->name, *tmp, strerror(errno), ms);
	}
	replace_pwd(ms);
	//ms->ret = 0;
	return 1;
}