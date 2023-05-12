#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>

int main()
{
	char *str;
	while (1)
	{
		str = readline("minishel>$ ");
	}
	return (0);
}
