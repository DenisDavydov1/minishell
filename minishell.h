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
# include "libft/libft.h"

# define MEMALLOC "memory allocation fail"
# define PARSEERR "parse error"
# define CMDNFERR ": command not found"
# define PERMISSIONERR ": Permission denied"

# define SET " <>;|"

typedef struct		s_cmd
{
	char			*name;
	char			**flag;
	char			**arg;
	int				pipe;
	int				write; // 0 - write to stdout, 1 - write to file, 2 - append to file
	char			*file; // write result of command to this file
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
	char		**path;
	//char		*home; //мб проще получить потом?
	t_cmd		*cmd;
	t_env		*env;
}				t_ms;

void ft_export_sort(t_env *env);
int throw_error(char *errtype, t_ms *ms);
void *e_malloc(size_t size);
void *e_calloc(size_t nmemb, size_t size);
char *e_strdup(char *s);
char **e_split(char *s, char c);
char **charxx_alloc(int size);
void charxx_free(char **s);
char **tenv_to_envp(t_env *env);

t_ms tms_init(void);
t_cmd *tcmd_init(t_ms *ms);
int tms_lineparse(t_ms *ms);

void tenv_print(t_env *env);

//add function
int msh_cd(t_ms *ms);
int msh_exit(t_ms *ms);
int msh_env(t_ms *ms);
int msh_export(t_ms *ms);
int msh_echo(t_ms *ms);
int msh_pwd(t_ms *ms);
int msh_unset(t_ms *ms);
int msh_launch(t_ms *ms);

//add utils for function
int ft_strcmp2(char *s1, char *s2, int count);
int ft_strcmp1(char *s1, char *s2);
char *find_in_env(t_ms *ms, char *s);
int find_and_replace_env(t_ms *ms, char *name, char *value);
int add_in_env(t_ms *ms, char *s);
void delete_from_env(t_ms *ms, char *s);
int tenv_len(t_env *env);
void charxx_swap(char **s1, char **s2);
void export_print(char **s);

void tcmd_free(t_ms *ms);

#endif
