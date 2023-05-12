#include "./minishell.h"

int main()
{
	char *str;
	while (1)
	{
		str = readline("minishel>$ ");
		system(str);
	}
	return (0);
}
