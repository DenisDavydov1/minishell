#include "minishell_p.h"

void	sigint_handler(int sn)
{
	if (write(1, "\b\b  \n", 5) < 0)
		return ;
	//display_prompt_msg();
    write(1, "minishell-1.0$ ", 15);
	signal(SIGINT, sigint_handler);
}

void	sigquit_handler(int sn)
{
	if (write(1, "\b\b  \b\b", 6) < 0)
		return ;
	return ;
}