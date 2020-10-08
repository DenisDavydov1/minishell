#include "minishell.h"

void *emalloc(size_t size)
{
	void *out;
	
	out = malloc(size);
	if (out)
		exit(EXIT_FAILURE);
	return (out);
}


int main(int argc, char **argv, char **env)
{
	
	t_env en;
	t_env *en1;
	
	en1 = (t_env *)emalloc(sizeof(t_env));

	en.next = en1;
	printf("%p\n", en.next);
	//for (int i=0; i<10; i++)
		//printf("%s\n", env[i]);
	
	return (0);
}
