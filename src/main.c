/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:14:27 by agladkov          #+#    #+#             */ /*   Updated: 2023/06/03 17:52:23 by agladkov         ###   ########.fr       */
/* ************************************************************************** */

#include "../minishell.h"

static void print_list(t_mlist *list)
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
			printf("argv[0]\t: %s\n", NULL);
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


int main(int argc, char **argv, char **menv)
{
	t_shell *shell;
	t_mlist *list;

	(void) argv;
	argc = 0;

	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->env = ft_create_envlist(menv);

	char *str;
	signal(SIGINT, ft_action);
	rl_catch_signals = 0;
	using_history();
	while (1)
	{
		str = readline("minishell>$ ");
		if (!str)
			return (1);
		else if (ft_strncmp("exit", str, 5) == 0)
		{
			printf("exit\n");
			exit(0);
		}
		list = ft_fill_list(shell, str);
		shell->list = &list;
		add_history(str);
		print_list(list);
		free(str);
		ft_pipex(*shell->list);
		ft_free_2_linked_list(shell->list);
	}
	return (0);
}
