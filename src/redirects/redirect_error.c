#include "minishell.h"

int	ft_redirect_unexpected_error(char *command)
{
		printf("syntax error near unexpected token `%s`\n", command); 
		rl_on_new_line();
		return (1);
}

void ft_redirect_error_argument(t_mlist *list, int n)
{
	if (list->argv[n + 1])
		ft_redirect_unexpected_error(list->argv[n + 1]);
	else
		ft_redirect_unexpected_error("newline");
}
