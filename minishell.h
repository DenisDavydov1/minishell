#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h> //strerror
#include <stdlib.h> //malloc, free, exit
#include <unistd.h> //write, read, fork, getcwd, \
					//chdir, execve, dup, dup2, pipe,
#include <fcntl.h> //open, close
#include <sys/wait.h> //wait, waitpid, wait3, wait4
#include <sys/stat.h> // stat, lstat, fstat
#include <sys/errno.h> //errno
#include <signal.h> //signal, kill
#include <dirent.h> //opendir, readdir, closedir

typedef struct	s_cmd
{
	
}				t_cmd;

typedef struct	s_env
{
	
}				t_env;

typedef struct	s_ms
{
	pid_t		pid;
	char		*name;
	char		*line;
	char		*path;
}				t_ms;

#endif
