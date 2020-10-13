#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //strerror
# include <stdlib.h> //malloc, free, exit
# include <unistd.h> //write, read, fork, getcwd, \
					//chdir, execve, dup, dup2, pipe,
# include <fcntl.h> //open, close
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/errno.h> //errno
# include <signal.h> //signal, kill
# include <dirent.h> //opendir, readdir, closedir
//# include "libft/libft.h"

# include "libft/libft.h"

# define MEMALLOC "memory allocation fail"
# define SEMICOLONERR "parse error near `;;'"
# define LESSERR "parse error near `<'"
# define PARSEERR "parse error"

# define SET " <>;|" // add pipe

typedef struct		s_cmd
{
	char			*name;
	char			**flag;
	char			**arg;
	int				pipe;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct	s_ms
{
	pid_t		pid;
	//char		*name;
	char		*line;
	char		*path;
	char		*home; //мб проще получить потом?
	t_cmd		*cmd;
	t_env		*env;
}				t_ms;

void ft_export_sort(t_env *env);
void throw_error(char *errtype);
void *e_malloc(size_t size);
void *e_calloc(size_t nmemb, size_t size);
char *e_strdup(char *s);
char **e_split(char *s, char c);
char **charxx_alloc(int size);
void charxx_free(char **s);
char **tenv_to_envp(t_env *env);

t_ms tms_init(void);
t_cmd *tcmd_init(t_ms *ms);

void tenv_print(t_env *env);

#endif
