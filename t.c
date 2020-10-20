#include <stdio.h>

int main(int ac, char **vc)
{
    if (vc && *vc)
        printf("%s\n", *(vc + 1));
    return (0);
}