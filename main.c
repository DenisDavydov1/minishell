#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
#include <string.h>
//#include <sys/wait.h>
#include "minishell.h"

//#define msh_RL_BUFSIZE 1024
//#define msh_TOK_BUFSIZE 64
//#define msh_TOK_DELIM " \t\r\n\a"

/*
	Объявление функций для встроенных команд оболочки:
 */

//int msh_minishell(char **args, t_ms *ms);


int ft_strcmp1(char *s1, char *s2) //заменить на либу?
{
	int i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

int ft_strcmp2(char *s1, char *s2, int count) //strncmp?
{
	int i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && i < count)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
	}
	return (1);
}

int ft_strcmp3(char *s1, char *s2)
{
	int i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
		{
			if (s1[i] > 64 && s1[i] < 91)
			{
				if (s1[i] != s2[i] + 32)
					return (0);
			}
			else
			{
				if (s1[i] != s2[i])
					return (0);
			}
			i++;
		}
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

char *find_in_env(t_ms *ms, char *s)
{
	t_env *tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strcmp2(tmp->name, s, ft_strlen(s)))
			return(tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int find_and_replace_env(t_ms *ms, char *name, char *value)
{
	t_env *tmp;
	char *old_value;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strcmp2(tmp->name, name, ft_strlen(name)))
		{
			old_value = tmp->value;
			tmp->value = value;
			free(old_value);
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int msh_minishell(char **args, t_ms *ms)
{
	char **envp;

	envp = tenv_to_envp(ms->env);
	execve("./minishell", NULL, envp);
	return (1);
}

int msh_execute(t_ms *ms)
{
	int ret;
	
	ret = 1;
	if (!ms->cmd->name)
		return (ret);
	else if (ft_strcmp3(ms->cmd->name, "echo"))
		return (ret = msh_echo(ms));
	else if (ft_strcmp3(ms->cmd->name, "cd"))
		return (ret = msh_cd(ms));
	else if (ft_strcmp3(ms->cmd->name, "pwd"))
		return (ret = msh_pwd(ms));
	else if (ft_strcmp3(ms->cmd->name, "export"))
		return (ret = msh_export(ms));
	else if (ft_strcmp3(ms->cmd->name, "unset"))
		return (ret = msh_unset(ms));
	else if (ft_strcmp3(ms->cmd->name, "env"))
		return (ret = msh_env(ms));
	else if (ft_strcmp3(ms->cmd->name, "exit"))
		return (ret = msh_exit(ms));
	else
		return (ret = msh_launch(ms));
		//return (ret = run_bin(ms));
}

int ft_strcpy_my(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (0);
}

int get_next_line(char **line)
{
	char buf;
	char *new;
	int count;
	int i;

	i = 0;
	if (!(*line = (char*)e_malloc(sizeof(char))))
		return (-1);
	*line[0] = '\0';
	while ((count = read(0, &buf, 1)) > 0 && buf != '\n')
	{
		if (!(new = (char*)malloc(sizeof(char) * (i + 2))))
			return (-1);
		ft_strcpy_my(*line, new);
		free(*line);
		new[i++] = buf;
		new[i] = '\0';
		*line = new;
	}
	new = NULL;
	return(count);
}

int msh_loop(t_ms *ms)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		//printf("minishell-1.0$ ");
		get_next_line(&ms->line);
		if (ft_strlen(ms->line) > 0)
		{
			tms_lineparse(ms);
			status = msh_execute(ms);
		}
		free(ms->line);
	}
	return (0);
}

t_env *tenv_init(char *name, char *value)
{
	t_env *env;

	env = (t_env *)e_malloc(sizeof(t_env));
	env->name = name;
	env->value = value;
	env->next = NULL;
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

int main(int argc, char **argv, char **envp)
{
	// Загрузка файлов конфигурации при их наличии.

	// Запуск цикла команд.
	t_ms ms;
	//pid_t pid, wpid;
	//int status;

	tenv_set(&ms, envp);
	/*if (!(pid = fork()))
	{
		if (!(msh_loop(&ms)))
		{
			perror("msh");
			exit(EXIT_FAILURE);
		}

		else // Родительский процесс
		{
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
	while ((wpid = wait(&status)) > 0)
		NULL;*/
	msh_loop(&ms);

	// Выключение / очистка памяти.

	return EXIT_SUCCESS;
}