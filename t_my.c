#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int test(char **s)
{
	printf("s = %s  s_test_address = %p \n", *s, &(*s));
	free(*s);
	*s = NULL;
	return 0;
}

int main()
{
	char *s;

	s = strdup("HELLO!");
	printf("s = %s  s_address = %p \n", s, &s);
	test(&s);
	printf("s = %s  s_address = %p \n", s, &s);
    return (0);
}