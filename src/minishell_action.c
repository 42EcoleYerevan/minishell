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

void ctrl_d_handler(char *str)
{
	if (!str)
	{
		printf("\033[1A\033[12Cexit\n");
		exit(0);
	}
}

void	ft_init_action(void)
{
	signal(SIGINT, ft_action);
	signal(SIGQUIT, ft_quit);
}