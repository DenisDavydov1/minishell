#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	for (int i=0; i<10; i++)
		printf("%s\n", env[i]);
	return (0);
}
