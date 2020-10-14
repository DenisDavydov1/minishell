#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
#include <string.h>
//#include <sys/wait.h>
#include "minishell.h"

#define msh_RL_BUFSIZE 1024
#define msh_TOK_BUFSIZE 64
#define msh_TOK_DELIM " \t\r\n\a"

/*
	Объявление функций для встроенных команд оболочки:
 */

int msh_minishell(char **args, t_ms *ms);


int ft_strcmp1(char *s1, char *s2)
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

int ft_strcmp2(char *s1, char *s2, int count)
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

/*static char	**free_arr(char **arr)
{
	unsigned int i;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}*/

/*int msh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
} */

/*
	Реализации встроенных функций
*/
char *find_in_env(t_ms *ms, char *s)
{
	t_env *tmp;

	tmp = ms->env;
	while (tmp->next)
	{
		if (ft_strcmp2(tmp->name, s, ft_strlen(s)))
			return(tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void replace_pwd(t_ms *ms)
{
	t_env *tmp;
	t_env *pwd;
	t_env *old_pwd;

	tmp = ms->env;
	while (tmp->next)
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
	pwd->value = getcwd(pwd->value, 0); //убрать эту функцию и передавать путь вручную?
}

void add_in_env(t_ms *ms, char *s)
{
	char **test;
	t_env *tmp;

	test = e_split(s, '=');
	tmp = ms->env;
	while (tmp->next && tmp->next->name)
		tmp = tmp->next;
	tmp->next = (t_env *)e_malloc(sizeof(t_env));
	tmp->next->name = test[0];
	tmp->next->value = test[1];
	tmp->next->next = NULL;
	free(test);
}

void delete_from_env(t_ms *ms, char *s)
{
	t_env *tmp;
	t_env *prev;

	tmp = ms->env;
	prev = tmp;
	while (tmp && tmp->name)
	{
		if (ft_strcmp1(tmp->name, s))
		{
			if (prev == tmp)
				ms->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int msh_pwd(t_ms *ms)
{
	char *s;

	s = find_in_env(ms, "PWD");
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	return (1);
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

int msh_echo(t_ms *ms)
{
	char **flag;
	char **arg;

	flag = ms->cmd->flag;
	arg = ms->cmd->arg;
	if (flag && *flag && ft_strcmp1(*flag, "-n"))
	{
		if (arg && *arg)
		{
			while (*arg)
			{
				write(1, *arg, ft_strlen(*arg));
				arg++;
			}
		}
	}
	else
	{
		if (arg && *arg)
		{
			while (*arg)
			{
				write(1, *arg, ft_strlen(*arg));
				arg++;
			}
		}
		write(1, "\n", 1);
	}


	/*if (ft_strcmp1(args[1], "-n"))
		write(1, args[2], ft_strlen(args[2]));
	else
	{
		write(1, args[1], ft_strlen(args[1]));
		write(1, "\n", 1);
	}*/
	return 1;
}

int msh_exit(t_ms *ms)
{
	//return 0;
	exit(0);
}

int msh_env(t_ms *ms)
{
	t_env *tmp;

	tmp = ms->env;
	while (tmp && tmp->name)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (1);
}

int msh_export(t_ms *ms)
{
	char **tmp;

	tmp = ms->cmd->arg;

	if (tmp && *tmp)
	{
		while (*tmp)
		{
			add_in_env(ms, *tmp);
			tmp++;
		}
	}
	else
		ft_export_sort(ms->env);
	return(1);
}

int msh_unset(t_ms *ms)
{
	char **tmp;

	tmp = ms->cmd->arg;

	if (tmp && *tmp)
	{
		while (*tmp)
		{
			delete_from_env(ms, *tmp);
			tmp++;
		}
	}
	//if (args[1])
	//	delete_from_env(ms, args[1]);
	return (1);
}

int msh_minishell(char **args, t_ms *ms)
{
	char **envp;

	envp = tenv_to_envp(ms->env);
	execve("./minishell", NULL, envp);
	return (1);
}

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
	char **argv;

	i = 0;
	flag = ms->cmd->flag;
	arg = ms->cmd->arg;
	argv = charxx_alloc(count_arg(ms));
	if (ms->cmd->name)
		argv[i++] = ms->cmd->name;
	if (flag && *flag)
	{
		while (*flag)
		{
			argv[i] = *flag;
			i++;
			flag++;
		}
	}
	if (arg && *arg)
	{
		while (*arg)
		{
			argv[i] = *arg;
			i++;
			arg++;
		}
	}
	return (argv);
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

void msh_loop(t_ms *ms)
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
/*
int main(int argc, char **argv, char **envp)
{
	// Загрузка файлов конфигурации при их наличии.

	// Запуск цикла команд.
	t_ms ms;
	t_env *env;
	t_env *first;

	tenv_set(&ms, envp);
	msh_loop(&ms);

	// Выключение / очистка памяти.

	return EXIT_SUCCESS;
}*/