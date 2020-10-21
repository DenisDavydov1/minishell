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
		res[i++] = ft_strdup(ms->cmd->name);
	if (flag && *flag)
	{
		while (*flag)
		{
			res[i] = ft_strdup(*flag);
			i++;
			flag++;
		}
	}
	if (arg && *arg)
	{
		while (*arg)
		{
			res[i] = ft_strdup(*arg);
			i++;
			arg++;
		}
	}
	return (res);
}

/*void	ft_error1(int err, char *exe, char *msg)
{
	ft_putstr_fd(exe, 1);
	ft_putchar_fd(':', 1);
	ft_putendl_fd(msg, 1);
	return (exit(err));
}*/

void close_pfd(t_ms *ms)
{
	if (ms->cmd->pipe)
		close(ms->cmd->pfd[1]);
	if (ms->cmd->prev && ms->cmd->prev->pipe)
		close(ms->cmd->prev->pfd[0]);
	if (ms->cmd->fd > 2)
		close(ms->cmd->fd);
}
int	execute_ps(char *ex, char **args, char **env, t_ms *ms)
{
	pid_t	pid;
	DIR *dir;
	//int tmp_fd;

	pid = fork();
	if (pid == 0)
	{
		if (ms->cmd->write > 0)
		{
			dup2(ms->cmd->fd, 1);
		}
		else if (ms->cmd->pipe)
		{
			dup2(ms->cmd->pfd[1], 1);
		}
		if (ms->cmd->prev && ms->cmd->prev->pipe)
		{
			dup2(ms->cmd->prev->pfd[0], 0);
			/*if (ms->cmd->pipe)
			{
				dup2(ms->cmd->pfd[1], 1);
			}*/
		}
		//dup2(ms->cmd->pfd[0], 0);
		//dup2(ms->cmd->pfd[1], 1);
		//printf("%d\n", pid);
		if (execve(ex, args, env) == -1)
		{
			//if (ft_strcmp2(ex, "./", 2))
			if (!ft_strncmp(ex, "./", 2))
				throw_error(PERMISSIONERR, ms);
			else if (ft_strchr(ex, '/'))
			{
				if (!(dir = opendir(ex)))
					throw_error(CDERR, ms);
				else
				{
					throw_error(ISADIRERR, ms);
					closedir(dir);
				}
			}
			else
				throw_error(CMDNFERR, ms);
		}
		
	}
	else if (pid < 0)
		ft_error(ex, NULL, "failed to fork", ms);
		//ft_error1(1, ex, "failed to fork"); //нужна ли эта ошибка?
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&pid);
		close_pfd(ms);
		/*if (ms->cmd->pipe)
			close(ms->cmd->pfd[1]);
		if (ms->cmd->prev && ms->cmd->prev->pipe)
			close(ms->cmd->prev->pfd[0]); */
	}
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	//printf("status = %d \n", WEXITSTATUS(pid));
	ms->ret = WEXITSTATUS(pid);
	//printf("status1 = %d \n", WEXITED);
	return (1);
}

int msh_launch(t_ms *ms)
{
	char **argv;

	char	**envp;
	char	**path;
	char 	*full_path;

	path = ms->path;
	/*if (!ft_strncmp(ms->cmd->name, "./", 2))
		full_path = ms->cmd->name;
	else
	{
		while(*path)
		{
			if ((full_path = find_path(ms->cmd->name, ms->path)))
				break;
			path++;
		}
	}*/
	while(*path)
	{
		if ((full_path = find_path(ms->cmd->name, ms->path)))
			break;
		path++;
	}
	if (!full_path)
		full_path = ms->cmd->name;
	argv = create_argv(ms);
	envp = tenv_to_envp(ms->env);
	execute_ps(full_path, argv, envp, ms);

	/*free(full_path);
	charxx_free(argv);
	charxx_free(envp);*/
	return 1;
}