#include "minishell.h"

void throw_error(char *errtype)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(errtype, 2);
	exit(EXIT_FAILURE);
}