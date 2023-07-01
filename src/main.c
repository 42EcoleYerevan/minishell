#include "minishell.h"

void print_list(t_mlist *list)
{
	int n;
	int l;

	l = 0;
	while (list)
	{
		printf("\033[33mlist #%d\n\033[0m", l++);
		printf("bin \t: %s\n", (list->bin));
		n = 0;
		while (list->argv[n])
		{
			printf("argv[%d]\t: %s\n", n, (list->argv[n]));
			n++;
		}
		if (list->argv[0] == NULL)
			printf("argv[0]\t: (null)\n");
		printf("command\t: %s\n", (list->command));
		if (list->next)
			printf("next\t: %p\n", list->next);
		else
			printf("next\t: NULL\n");
		if (list->prev)
			printf("prev\t: %p\n\n", list->prev);
		else
			printf("prev\t: NULL\n\n");
		list = list->next;
	}
}

void	executor(t_shell *shell)
{
	int		pid;
	t_mlist	*tmp;

	pid = 1;
	tmp = *shell->list;
	while (tmp)
	{
		if (tmp->bin || ft_isbuiltin(tmp->argv[0]))
		{
			if (tmp->next)
				pipe(tmp->fd);
			if (ft_isbuiltin(tmp->bin) || ft_isbuiltin(tmp->argv[0]))
				exit_status = ft_builtin_handler(shell, tmp);
			else
				exit_status = ft_executor(shell, tmp);
			if (exit_status != 0)
				return ;
		}
		else 
			printf("minishell: %s: command not found\n", tmp->argv[0]);
		tmp = tmp->next;
	}
	while(waitpid(-1, &exit_status, 0) != -1);
	exit_status = exit_status / 256;
}

void ft_event_loop(t_shell *shell)
{
	char	*str;
	t_mlist	*list;
	while (1)
	{
		str = readline("minishell>$ ");
		add_history(str);
		ctrl_d_handler(str);
		list = ft_fill_list(shell, str);
		shell->list = &list;
		/* print_list(list); */
		executor(shell);
		free(str);
		ft_free_2_linked_list(shell->list);
	}
}

int exit_status;

int	main(int argc, char **argv, char **menv)
{
	t_shell	*shell;

	(void) argv;

	if (argc == 1)
	{
		shell = (t_shell *)malloc(sizeof(t_shell));
		shell->env = ft_create_envlist(menv);
		/* ft_init_action(); */
		rl_catch_signals = 0;
		using_history();
		ft_event_loop(shell);
	}
	return (exit_status);
}
