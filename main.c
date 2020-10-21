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

//char **g_envp;
//t_ms g_ms;
//pid_t g_pid;

/*int ft_strcmp1(char *s1, char *s2) //заменить на либу?
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
}*/

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

/*
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
}*/

/*int ft_strcpy_my(char *s1, char *s2)
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
}*/
/*
int msh_loop(t_ms *ms)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		ft_putstr_fd("minishell-1.0$ ", 1);
		get_next_line(&ms->line);
		if (ft_strlen(ms->line) > 0)
		{
			if (tms_lineparse(ms))
				status = msh_execute(ms);
		}
		free(ms->line);
		tcmd_free(ms);
	}
	return (0);
}
*/

/*t_env *tenv_init(char *name, char *value)
{
	t_env *env;

	env = (t_env *)e_malloc(sizeof(t_env));
	if (!(ft_strcmp(name, "OLDPWD")))
	{
		env->name = name;
		env->value = NULL;
		env->next = NULL;
		free(value);
	}
	else
	{
		env->name = name;
		env->value = value;
		env->next = NULL;
	}
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
	//ms->home = ft_strdup(find_in_env(ms, "HOME"));
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
} */

int msh_set_fd(t_ms *ms)
{
	int fd;

	//pipe O_RDWR
	//printf("%d\n", ms->cmd->write);
	if (ms->cmd->write == -1)
		fd = 2;
	else if (ms->cmd->write == 0)
		fd = 1;
	else if(ms->cmd->write == 1)
	{
		if ((fd = open(ms->cmd->file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
			ft_error(NULL, ms->cmd->file, strerror(errno), ms);
	}
	else if(ms->cmd->write == 2)
	{
		if ((fd = open(ms->cmd->file, O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
			ft_error(NULL, ms->cmd->file, strerror(errno), ms);
	}
	return (fd);
}

/*add > < >> <>*/
int msh_execute(t_ms *ms)
{
	int ret;
	
	ret = 1;
	if (ft_strcmp3(ms->cmd->name, "echo"))
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

char	*get_next_line(char *command)
{
	char		buf[2];
	char		*cpy;

	buf[0] = ' ';
	buf[1] = '\0';
	while (buf[0] != '\n' && buf[0] == ' ')
	{
		if (!(read(0, buf, 1)))
			if (write(1, "exit\n", 5))
				exit(EXIT_SUCCESS);
	}
	if (!command)
		command = ft_strdup("");
	while (buf[0] != '\n')
	{
		if (!(cpy = ft_strdup(command)))
			return (NULL);
		free(command);
		if (!(command = ft_strjoin(cpy, buf)))
			return (NULL);
		free(cpy);
		//while (!(read(0, buf, 1)))
		if (!(read(0, buf, 1)))
			return (NULL);
			//if (write(1, " \b", 2) < 0)
			//	return (NULL);
	}
	return (command);
}

/*void display_prompt_msg()
{
	write(1, "minishell-1.0$ ", 16);
}*/

void msh_set_pfd(t_ms *ms)
{
	if (ms->cmd->pipe)
	{
		if (pipe(ms->cmd->pfd) == -1)
			throw_error(PIPEERR, NULL);
		if (ms->cmd->fd < 3)
			ms->cmd->fd = ms->cmd->pfd[1];
	}
}

int msh_loop(t_ms *ms)
{
	write(1, "minishell-1.0$ ", 15);
	//get_next_line(&ms->line);
	ms->line = NULL;
	ms->line = get_next_line(ms->line);
	if (ms->line && *ms->line && tms_lineparse(ms))
	{
		//tcmd_print(ms->cmd);
		while (ms->cmd)
		{
			tcmd_parse_quotes(ms);
			if (ms->cmd->name)// && !msh_execute(ms, p))
			{
				//printf("cmd name: %s\n", ms->cmd->name);
				ms->cmd->fd = msh_set_fd(ms);
				msh_set_pfd(ms);
				msh_execute(ms);
				close_pfd(ms);
				//if (!ms->cmd->pipe && ms->cmd->fd > 2)
				//if (ms->cmd->fd > 2)
				//	close(ms->cmd->fd);
			}
				
			if (!ms->cmd->next)
				break ;
			ms->cmd = ms->cmd->next;
		}
	}
	free(ms->line);
	ms->line = NULL;
	tcmd_free(ms);
	//ret 0 for signals exit
	return (1);
}

int ft_error(char *name, char *arg, char *error, t_ms *ms)
{
	ft_putstr_fd("minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	ms->ret = 1;
	return (0);
}

/*void	sigint_handler(int sn)
{
	if (write(1, "\b\b  \n", 5) < 0)
		return ;
	display_prompt_msg();
	signal(SIGINT, sigint_handler);
}

void	sigquit_handler(int nb)
{
	if (write(1, "\b\b  \b\b", 6) < 0)
		return ;
	return ;
}*/

int main(int argc, char **argv, char **envp)
{

	//pid_t wpid;
	//int status;
	// Загрузка файлов конфигурации при их наличии.

	// Запуск цикла команд.
	t_ms ms;

	ms = tms_init();
	tenv_set(&ms, envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (msh_loop(&ms))
		NULL;

	// Выключение / очистка памяти.

//если не делать fork и kill, а стирать символы и чистить структуру?
	return EXIT_SUCCESS;
}