#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *func(char *s)
{
	char *out;

	printf("in func: %p\n", &s);
	out = strdup("new_name");
	free(s);
	return (out);
}

int main()
{
	char *name;

	name = strdup("some_name");
	printf("before func: %p\n", &name);
	name = name ? func(name) : name;
	printf("after func: %p\n", &name);
	printf("new name: %s\n", name);
	free(name);
	return (0);
}