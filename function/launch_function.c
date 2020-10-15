#include "minishell.h"

char	*find_path(char *name, char **path)
{
	char	*full_path;
	int		i;
	void	*stat;
	char *exec;

	exec = ft_strjoin("/", name);
	if (!(stat = malloc(sizeof(struct stat))))
		return (NULL);
	i = 0;
	full_path = NULL;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], exec);
		if (!lstat(full_path, stat))
		{
			free(exec);
			free(stat);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(exec);
	free(stat);
	return (NULL);
}


/*char *unite_str(char *path)
{
	int i = 0;
	int j = 0;
	char *res;
	char s[5] = "/bin/";

	res = malloc(ft_strlen(path) + 6);
	while (i < 5)
	{
		res[i] = s[i];
		i++;
	}
	while (j < ft_strlen(path))
	{
		res[i] = path[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}*/

int count_arg(t_ms *ms)
{
	int i;
	char **flag;
	char **arg;

	i = 0;
	flag = ms->cmd->flag;
	arg = ms->cmd->arg;
	if (ms->cmd->name)
		i++;
	if (flag && *flag)
	{
		while (*flag)
		{
			i++;
			flag++;
		}
	}
	if (arg && *arg)
	{
		while (*arg)
		{
			i++;
			arg++;
		}
	}
	return (i);
}

char **create_argv(t_ms *ms)
{
	int i;
	char **flag;
	char **arg;
	char **res;

	i = 0;
	flag = ms->cmd->flag;
	arg = ms->cmd->arg;
	res = charxx_alloc(count_arg(ms));
	if (ms->cmd->name)
		res[i++] = ms->cmd->name;
	if (flag && *flag)
	{
		while (*flag)
		{
			res[i] = *flag;
			i++;
			flag++;
		}
	}
	if (arg && *arg)
	{
		while (*arg)
		{
			res[i] = *arg;
			i++;
			arg++;
		}
	}
	return (res);
}

int msh_launch(t_ms *ms)
{
	pid_t pid, wpid;
	int status;
	char **argv;

	char	**envp;
	char	**path;
	char 	*full_path;

	path = ms->path;
	if (!ft_strncmp(ms->cmd->name, "./", 2))
	{
		full_path = ms->cmd->name;
		printf("fullpath = %s \n", full_path);
		//argv = NULL;
		//envp = tenv_to_envp(ms->env);
		//execve(full_path, argv, envp);
		//while (!WIFEXITED(status) && !WIFSIGNALED(status))
		//		wpid = waitpid(pid, &status, WUNTRACED);
	}
	else
	{
		while(*path)
		{
			if ((full_path = find_path(ms->cmd->name, ms->path)))
				break;
			path++;
		}
		//argv = create_argv(ms);
	}
	argv = create_argv(ms);
	envp = tenv_to_envp(ms->env);
	pid = fork();
	//char *path = unite_str(ms->cmd->name);
	//printf("fullpath = %s \n", full_path);
	//argv[0] = full_path;
	printf("pid = %d \n", pid);

	if (pid == 0) // Дочерний процесс
	{
		//if (execvp(args[0], args) == -1)
		//if (execve(path, args, NULL) == -1) //нужно ли вообще envp?
		if (execve(full_path, argv, envp) == -1) //нужно ли вообще envp?
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0) // Ошибка при форкинге
			perror("msh");
		else // Родительский процесс
		{
			//while (!WIFEXITED(status) && !WIFSIGNALED(status))
			//	wpid = waitpid(pid, &status, WUNTRACED);
			while ((wpid = wait(&status)) > 0)
				NULL;
		}
	}
	free(full_path);
	//charxx_free(argv);
	//charxx_free(envp);
	return 1;
}