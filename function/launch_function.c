#include "minishell.h"

char *unite_str(char *path)
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
}

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

	argv = create_argv(ms);
	pid = fork();
	char *path = unite_str(ms->cmd->name);

	if (pid == 0) // Дочерний процесс
	{
		//if (execvp(args[0], args) == -1)
		//if (execve(path, args, NULL) == -1) //нужно ли вообще envp?
		if (execve(path, argv, NULL) == -1) //нужно ли вообще envp?
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0) // Ошибка при форкинге
			perror("msh");
		else // Родительский процесс
		{
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
	free(path);
	charxx_free(argv);
	return 1;
}