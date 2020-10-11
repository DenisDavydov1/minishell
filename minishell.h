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

# define SET " <>;" // add pipe

typedef struct		s_cmd
{
	char			name[255];
	//char			**flag;
	//char			**arg;
	char			flag[20][100];
	char			arg[20][255]; //getconf ARG_MAX
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

#endif
