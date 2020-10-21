#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //strerror
# include <string.h> //strerror
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
# define CDERR ": No such file or directory"
# define ISADIRERR ": is a directory" //сложно обработать
# define PIPEERR ": pipe error"


# define SET " <>;|"
# define QUOTES "\'\""

/*
** write:	-1 - write to stderr,
**			0 - write to stdout,
**			1 - write to file,
**			2 - append to file
*/

typedef struct		s_cmd
{
	char			*name;
	char			**flag;
	char			**arg;
	int				pipe;
	int				write;
	int				fd;
	char			*file;
	int				pfd[2];
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
	int			ret;
	t_cmd		*cmd;
	t_env		*env;
}				t_ms;

//void ft_export_sort(t_ms *ms);
int throw_error(char *errtype, t_ms *ms);
char **tenv_to_envp(t_env *env);
void tenv_set(t_ms *ms, char **envp);
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
//void delete_from_env(t_ms *ms, char *s);
int tenv_len(t_env *env);
void charxx_swap(char **s1, char **s2);
void export_print(char **s, t_ms *ms);

int ft_error(char *name, char *arg, char *error, t_ms *ms);
int check_env_name(t_ms *ms, char *s);


void sigint_handler(int sn);
void sigquit_handler(int sn);


//char **split_replace_quotes(char **s, t_ms *ms);

void close_pfd(t_ms *ms);

int msh_set_fd(t_ms *ms);
void msh_set_pfd(t_ms *ms);
char	*get_next_line(char *command);
int	count_arg(t_ms *ms);
int ft_strcmp_reg(char *s1, char *s2);





/*
** [e_functions_a.c - e_functions_b.c]
*/

void *e_malloc(size_t size);
void *e_calloc(size_t nmemb, size_t size);
char *e_strdup(char *s);
char **e_split(char *s, char c);
char *e_substr(char *s, int start, int len);
char *e_strjoin(char *s1, char *s2);
char *e_itoa(int n);

/*
** [parser_common_utils_a.c - parser_common_utils_d.c]
*/

int in_set(char c, char *set);
int is_flag(char *s);
int tcmd_isempty(t_cmd *cmd);
t_cmd *tcmd_gotoempty(t_cmd *cmd);
t_cmd *tcmd_gotocmdbegin(t_cmd *cmd);
t_cmd *tcmd_gotolast(t_cmd *cmd, char *s);
t_cmd *tcmd_has_cmd(t_cmd *cmd);
t_cmd *tcmd_get_cmd(t_cmd *cmd);
char **tcmd_set_name(t_ms *ms, char **s);
char **tcmd_addflag(t_ms *ms, char **s);
char **tcmd_addarg(t_ms *ms, char **s);
char **tcmd_semicolon(t_ms *ms, char **s);
char **tcmd_pipe(t_ms *ms, char **s);
void charxx_free(char **s);
char **charxx_alloc(int size);
int charxx_len(char **ss);
char **charxx_insert(char **ss, char *s, int pos);
char **charxx_delete_one(char **ss, int pos);

/*
** [parser_main.c]
*/

int tms_lineparse(t_ms *ms);

/*
** [parser_optimize_a.c - parser_optimize_e.c]
*/

void tcmd_optimize(t_ms *ms);
void tcmd_put_arg_to_name(t_ms *ms);
void tcmd_move_pipes(t_ms *ms);
void tcmd_divide_args(t_ms *ms);
void tcmd_flags_to_args(t_ms *ms);
void tcmd_remove_nulls(t_ms *ms);
void tcmd_replace_lg(t_ms *ms);
int tcmd_delete_cmd_if_equal(t_ms *ms);
t_cmd *tcmd_delete_cmd(t_ms *ms, t_cmd *ptr);
void tcmd_optimize_signs(t_ms *ms);
void tcmd_remove_signs(t_ms *ms);
void tcmd_put_args_to_cmd(t_ms *ms);

/*
** [parser_quotes_a.c - parser_quotes_b.c]
*/

void		tcmd_parse_quotes(t_ms *ms);
char		*parse_single_quote(char *s, int *i);
char		*pq_add_char(char *out, char *s, int *i);
char		*pq_add_var(char *out, char *s, int *i, t_ms *ms);

/*
** [parser_splitset_a.c - parser_splitset_b.c]
*/

int is_esc_char(char *s, int *i);
int get_quote_end(char *s, char quote, int *start);
char	**free_arr(char **arr);
char		**e_splitset(char *s, char *set);
int split_countflags(char **s);
int split_countargs(char **s);
char	**arralloc(char *s, char *set);

/*
** [parser_tcmd_utils_a.c - parser_tcmd_utils_b.c]
*/

t_cmd *tcmd_gotofirst(t_cmd *cmd);
t_cmd *tcmd_init(t_ms *ms);
t_cmd *tcmd_insert(t_cmd *to);
t_ms tms_init(void);
void tcmd_free(t_ms *ms);
void tcmd_free_one(t_cmd *cmd);
char **tcmd_skip(char **s);
void tcmd_newtcmd(t_ms *ms);
int tcmd_set(t_ms *ms, char **s);

/*
** [parser_validity_a.c - parser_validity_b.c]
*/

int split_validity(char **s);
int split_validity_skip(char **s);

#endif
