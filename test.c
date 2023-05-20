#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int fd[2];
	int p = pipe(fd);
	if (p == -1)
		return (1);
	int pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		write(1, "hello", 5);
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		char str[100];
		close(fd[1]);
		close(fd[0]);
		dup2(fd[0], 0);
		read(0, str, 5);
		printf("%s\n", str);
		exit(0);
	}
	return (0);
}
