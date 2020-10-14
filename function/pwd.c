#include "minishell.h"

int msh_pwd(t_ms *ms)
{
	char *s;

	s = find_in_env(ms, "PWD");
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	return (1);
}