#include <signal.h>
#include <stdio.h>

void signal_handler(int signal);
void loop(void);

void s(int sig)
{
    loop();
}

void signal_handler(int signal)
{
    printf("Received signal %d\n", signal);
    s(1);
}

/*void signal_handler(int signal)
{
    printf("Received signal %d\n", signal);
}*/


void loop(void)
{
    //signal(SIGINT, signal_handler);
    printf("loop start\n");
    while (1)
        ;
}
int func(void)
{
    return (2);
}

int main(void)
{
    //signal(SIGINT, signal_handler);
    //sigpending ();
   //s(1);
    //loop();
/*
    signal(SIGINT, handle_sigint); 
    while (1) 
    { 
        printf("hello world\n"); 
        sleep(1); 
    } 
    return 0; 
    */
   printf("%d\n", func() % 256);
    return (func());
}