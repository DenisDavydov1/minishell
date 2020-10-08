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

typedef struct		s_cmd
{
	char			*name;
	char			**flag;
	char			**args;
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
}				t_ms;

#endif

/* > не должен перезаписывать файл полностью, а должен записать сначала файла */

/*
 # | Expression  | Result      | Comments
---+-------------+-------------+--------------------------------------------------------------------
 1 | "$a"        | apple       | variables are expanded inside ""
 2 | '$a'        | $a          | variables are not expanded inside ''
 3 | "'$a'"      | 'apple'     | '' has no special meaning inside ""
 4 | '"$a"'      | "$a"        | "" is treated literally inside ''
 5 | '\''        | **invalid** | can not escape a ' within ''; use "'" or $'\'' (ANSI-C quoting)
 6 | "red$arocks"| red         | $arocks does not expand $a; use ${a}rocks to preserve $a
 7 | "redapple$" | redapple$   | $ followed by no variable name evaluates to $
 8 | '\"'        | \"          | \ has no special meaning inside ''
 9 | "\'"        | \'          | \' is interpreted inside "" but has no significance for '
10 | "\""        | "           | \" is interpreted inside ""
11 | "*"         | *           | glob does not work inside "" or ''
12 | "\t\n"      | \t\n        | \t and \n have no special meaning inside "" or ''; use ANSI-C quoting
13 | "`echo hi`" | hi          | `` and $() are evaluated inside ""
14 | '`echo hi`' | `echo hi`   | `` and $() are not evaluated inside ''
15 | '${arr[0]}' | ${arr[0]}   | array access not possible inside ''
16 | "${arr[0]}" | apple       | array access works inside ""
17 | $'$a\''     | $a'         | single quotes can be escaped inside ANSI-C quoting
18 | "$'\t'"     | $'\t'       | ANSI-C quoting is not interpreted inside ""
19 | '!cmd'      | !cmd        | history expansion character '!' is ignored inside ''
20 | "!cmd"      | cmd args    | expands to the most recent command matching "cmd"
21 | $'!cmd'     | !cmd        | history expansion character '!' is ignored inside ANSI-C quotes
---+-------------+-------------+--------------------------------------------------------------------
*/


/*
QUOTES

MYVAR=sometext
echo "double quotes gives you $MYVAR"
echo 'single quotes gives you $MYVAR'

will give this:

double quotes gives you sometext
single quotes gives you $MYVAR
*/

/*
PIPES

echo a | cat -e < 2
эквивалентно 
echo a > aa
cat -e < aa < 2
*/