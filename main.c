#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/*
	Объявление функций для встроенных команд оболочки:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_echo(char **args);

/*
	Список встроенных команд, за которыми следуют соответствующие функции
 */
char *builtin_str[] = {
	"cd",
	"help",
	"exit",
	"echo",
	"pwd",
	"export",
	"unset",
	"env"
};

int (*builtin_func[]) (char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit,
	&lsh_echo
};

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
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

int lsh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

/*
	Реализации встроенных функций
*/
int lsh_cd(char **args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "lsh: ожидается аргумент для \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("lsh");
		}
	}
	return 1;
}

int lsh_help(char **args)
{
	int i;
	printf("LSH Стивена Бреннана\n");
	printf("Наберите название программы и её аргументы и нажмите enter.\n");
	printf("Вот список встроенных команд:\n");

	for (i = 0; i < lsh_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Используйте команду man для получения информации по другим программам.\n");
	return 1;
}

int lsh_echo(char **args)
{
	//printf ("args = |%s| \n", args[1]);
	if (ft_strcmp(args[1], "-n"))
		write(1, args[2], ft_strlen(args[2]));
	else
	{
		write(1, args[1], ft_strlen(args[1]));
		write(1, "\n", 1);
	}
	return 1;
}

int lsh_exit(char **args)
{
	return 0;
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

int lsh_launch(char **args, char **envp)
{
	pid_t pid, wpid;
	int status;
	//char **args;
	//*args = "/bin/ls";

	pid = fork();
	//printf("args[0] = %s \n", args[0]);
	char *path = unite_str(args[0]);
	//printf("path = %s \n", path);

	if (pid == 0) // Дочерний процесс
	{
		//if (execvp(args[0], args) == -1)
		if (execve(path, args, NULL) == -1)
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
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "lsh: ошибка выделения памяти\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
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

int lsh_execute(char **args, char **envp)
{
	int i = 0;

	if (args[0] == NULL) // Была введена пустая команда.
			return 1;
	while (i < lsh_num_builtins())
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
		i++;
	}
	return lsh_launch(args, envp);
}

void lsh_loop(char **envp)
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
		status = lsh_execute(args, envp);
		free(line);
		free(args);
	}
}

int main(int argc, char **argv, char **envp)
{
	// Загрузка файлов конфигурации при их наличии.

	// Запуск цикла команд.
	lsh_loop(envp);

	// Выключение / очистка памяти.

	return EXIT_SUCCESS;
}