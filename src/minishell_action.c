#include "../minishell.h"

void	ft_action(int sig)
{
	sig = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_quit(int sig)
{
	sig = 0;
	rl_redisplay();
}
