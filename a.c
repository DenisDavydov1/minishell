#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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
	//int fd[2];
	pid_t p;

	/*
	fd[0] = open("a", O_RDWR);
	fd[1] = dup(fd[0]);
	printf("%d %d\n", fd[0], fd[1]);
	write(fd[1], "123456", 6);
	close(fd[0]);
	close(fd[1]);
	*/
	/*
	if (pipe(fd) < 0)
		return (1);
	char str[] = "hello";
	
	write(fd[1], str, strlen(str));
	close(fd[1]);
	if ((p = fork()) < 0)
		return (0);
	if (p > 0)
	{
		close(fd[0]);
	}
	if (p == 0)
	{
		char buf[100];
		memset(buf, 0, 100);
		//close(fd[1]);
		read(fd[0], buf, 100);
		close(fd[0]);
		printf("%s\n", buf);
	}*/


	/*
	if ((p = fork()) < 0)
		return (0);
	else if (p > 0)
	{
		close(fd[0]);
		write(fd[1], str, strlen(str));
		close(fd[1]);
		//wait(NULL);
	}
	else
	{
		char buf[100];
		memset(buf, 0, 100);
		close(fd[1]);
		read(fd[0], buf, 100);
		close(fd[0]);
		printf("%s\n", buf);
	}*/
	/*
	if (pipe(fd) < 0)
		return (1);
	char str[] = "hello";
	write(fd[1], str, strlen(str));
	close(fd[1]);
	char buf[100];
	memset(buf, 0, 100);
	read(fd[0], buf, 100);
	close(fd[0]);
	printf("%s\n", buf);
	*/
	/*
	int fd[2];
	pipe(fd);
	write(fd[1], "123456", 6);
	close(fd[1]);
	char *args[] = {"cat", NULL};
	dup2(fd[0], 0);
	//close(0);
	execve("/bin/cat", args, NULL);
	//printf("123\n");
	//dup2(0, 0);
	//printf("!!\n");
	*/

	int fd[2];
	//fd[0] = 0;
	//fd[1] = 1;
	pipe(fd);
	//printf("%d %d\n", fd[0], fd[1]);
	write(fd[1], "asdfas\n", 7);
	close(fd[1]);
	p = fork();
	if (p == 0)
	{
		
		dup2(fd[0], 0);
		//printf("%d %d\n", fd[0], fd[1]);
		char *args[] = {"cat", "-e", NULL};
		execve("/bin/cat", args, NULL);
	}
	else
	{
		//close(fd[1]);
		wait(&p);
		//close(fd[0]);
	}
	
	
	return (0);
}