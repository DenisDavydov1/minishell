#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
char *func(char *s)
{
	char *out;

	printf("in func: %p\n", s);
	out = strdup("new_name");
	free(s);
	return (out);
}

int main(void)
{
	char *name;

	name = strdup("some_name");
	printf("before func: %p\n", name);
	name = name ? func(name) : name;
	printf("after func: %p\n", name);
	printf("new name: %s\n", name);
	free(name);
	return (0);
}*/

char *func(char *s)
{
	free(s); // очистка содержимого по копии указателя
	s = NULL; // нулю присваивается копия указателя а не он сам
}

int main(void)
{
	char *name;

	name = strdup("some_name");
	printf("before func: %s\n", name);
	func(name); // указатель остался, и его значение не меняется, но содержимое очищено
	//printf("new name: >%s< (%s)\n", name, name ? "NOT NULL" : "NULL");
	return (0);
}