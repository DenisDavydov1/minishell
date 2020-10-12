#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
#include <string.h>
//#include <sys/wait.h>
#include "minishell.h"

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/*
	Объявление функций для встроенных команд оболочки:
 */
int lsh_cd(char **args, t_ms *ms);
int lsh_pwd(char **args, t_ms *ms);
int lsh_exit(char **args, t_ms *ms);
int lsh_echo(char **args, t_ms *ms);
int lsh_env(char **args, t_ms *ms);
int lsh_export(char **args, t_ms *ms);
int lsh_unset(char **args, t_ms *ms);

/*
	Список встроенных команд, за которыми следуют соответствующие функции
 */
char *builtin_str[] = {
	"cd",
	"pwd",
	"exit",
	"echo",
	"env",
	"export",
	"unset"
	};

int (*builtin_func[])(char **, t_ms *) = {
	&lsh_cd,
	&lsh_pwd,
	&lsh_exit,
	&lsh_echo,
	&lsh_env,
	&lsh_export,
	&lsh_unset};


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

int lsh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

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
	pwd->value = getcwd(pwd->value, 0);
}

void add_in_env(t_ms *ms, char *s)
{
	char **test;
	t_env *tmp;

	test = ft_split(s, '=');
	tmp = ms->env;
	while (tmp->next && tmp->next->name)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp->next->name = test[0];
	tmp->next->value = test[1];
	tmp->next->next = NULL;
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

int lsh_pwd(char **args, t_ms *ms)
{
	char *s;
	s = find_in_env(ms, "PWD");
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	return (1);
}

int lsh_cd(char **args, t_ms *ms)
{
	char *s;
	if (args[1] == NULL)
	{
		s = find_in_env(ms, "HOME"); //потерянный указатель?
		if (chdir(s) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	replace_pwd(ms);

	return 1;
}

int lsh_echo(char **args, t_ms *ms)
{
	if (ft_strcmp1(args[1], "-n"))
		write(1, args[2], ft_strlen(args[2]));
	else
	{
		write(1, args[1], ft_strlen(args[1]));
		write(1, "\n", 1);
	}
	return 1;
}

int lsh_exit(char **args, t_ms *ms)
{
	return 0;
}

int lsh_env(char **args, t_ms *ms)
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

int lsh_export(char **args, t_ms *ms)
{
	t_env *tmp;

	if (args[1])
		add_in_env(ms, args[1]);
	return(1);
}

int lsh_unset(char **args, t_ms *ms)
{
	if (args[1])
		delete_from_env(ms, args[1]);
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

int lsh_launch(char **args, t_ms *ms)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	//printf("args[0] = %s \n", args[0]);
	char *path = unite_str(args[0]);
	//printf("path = %s \n", path);

	if (pid == 0) // Дочерний процесс
	{
		//if (execvp(args[0], args) == -1)
		if (execve(path, args, NULL) == -1) //нужно ли вообще envp?
		//if (execve("/bin/pwd", args, envp) == -1)
		{
			perror("lsh");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0) // Ошибка при форкинге
			perror("lsh");
		else // Родительский процесс
		{
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
	return 1;
}

char **lsh_split_line(char *line)
{
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "lsh: ошибка выделения памяти\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "lsh: ошибка выделения памяти\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

char *lsh_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0; // getline сама выделит память
	getline(&line, &bufsize, stdin);
	return line;
}

int lsh_execute(char **args, t_ms *ms)
{
	int i = 0;

	if (args[0] == NULL) // Была введена пустая команда.
		return 1;
	while (i < lsh_num_builtins())
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args, ms);
		i++;
	}
	return lsh_launch(args, ms);
}

void lsh_loop(t_ms *ms)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		//printf("> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		//printf("line = %s\n", line);
		status = lsh_execute(args, ms);
		free(line);
		free(args);
	}
}

int main(int argc, char **argv, char **envp)
{
	// Загрузка файлов конфигурации при их наличии.

	// Запуск цикла команд.
	t_ms ms;
	t_env *env;
	t_env *first;
	char **test;
	int i = 0;
	env = malloc(sizeof(t_env));
	first = env;
	while (envp[i])
	{
		test = ft_split(envp[i], '=');
		env->name = test[0];
		env->value = test[1];
		if (envp[i++])
		{
			env->next = malloc(sizeof(t_env));
			env = env->next;
		}
	}
	env->next = NULL;
	env = first;
	ms.env = env;
	/*while (first->name)
	{
		printf("name = %s \n value = %s \n", first->name, first->value);
		first = first->next;
	}*/
	lsh_loop(&ms);

	// Выключение / очистка памяти.

	return EXIT_SUCCESS;
}

//  gcc main.c libft/libft.a