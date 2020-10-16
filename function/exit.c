#include "minishell.h"

int msh_exit(t_ms *ms)
{
	//return 0;
	ft_putendl_fd("exit", 1); //убрать или оставить?
	exit(0);
}