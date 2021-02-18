/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:22:25 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:40:54 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *name, char **path)
{
	char	*full_path;
	int		i;
	void	*stat;
	char	*exec;

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

static void	exec_child(char *ex, char **args, char **env, t_ms *ms)
{
	DIR *dir;

	if (ms->cmd->write > 0)
		dup2(ms->cmd->fd, 1);
	else if (ms->cmd->pipe)
		dup2(ms->cmd->pfd[1], 1);
	if (ms->cmd->prev && ms->cmd->prev->pipe)
		dup2(ms->cmd->prev->pfd[0], 0);
	if (execve(ex, args, env) == -1)
	{
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

int			execute_ps(char *ex, char **args, char **env, t_ms *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child(ex, args, env, ms);
	else if (pid < 0)
		ft_error(ex, NULL, "failed to fork", ms);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&pid);
		close_pfd(ms);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	ms->ret = WEXITSTATUS(pid);
	return (1);
}

static char	*check_path(t_ms *ms)
{
	char	**path;
	char	*full_path;
	char	**ptr;

	full_path = NULL;
	path = e_split(find_in_env(ms, "PATH"), ':');
	ptr = path;
	if (path && *path)
		while (*path)
		{
			if ((full_path = find_path(ms->cmd->name, path)))
				break ;
			path++;
		}
	if (!full_path)
		full_path = ms->cmd->name;
	charxx_free(ptr);
	return (full_path);
}

int			msh_launch(t_ms *ms)
{
	char	**argv;
	char	**envp;
	char	*full_path;

	full_path = check_path(ms);
	argv = create_argv(ms);
	envp = tenv_to_envp(ms->env);
	execute_ps(full_path, argv, envp, ms);
	if (ft_strcmp(full_path, ms->cmd->name))
		free(full_path);
	charxx_free(argv);
	charxx_free(envp);
	return (1);
}
