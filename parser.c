#include "minishell.h"

void *emalloc(size_t size)
{
	void *out;
	
	out = malloc(size);
	if (out)
		exit(EXIT_FAILURE);
	return (out);
}



void cmd_line_parse(t_ms *ms)
{
	
}

int main(int argc, char **argv, char **env)
{
	
	return (0);
}
