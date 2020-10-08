#include <unistd.h>
#include <errno.h>
int main(void)
{
    write(-1, "", 1);
    return (errno);
}
