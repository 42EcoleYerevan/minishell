/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:14:27 by agladkov          #+#    #+#             */
/*   Updated: 2023/06/03 13:59:25 by agladkov         ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"

static void print_list(t_mlist *list)
{
	int n;
	while (list)
	{
		printf("bin \t: %s\n", (list->bin));
		n = 0;
		while (list->argv[n])
		{
			printf("argv[%d]\t: %s\n", n, (list->argv[n]));
			n++;
		}
		if (list->argv[0] == NULL)
			printf("argv[0] \t: %s\n", NULL);
		printf("command\t: %s\n", (list->command));
		printf("next\t: %p\n", list->next);
		printf("prev\t: %p\n\n", list->prev);
		list = list->next;
	}
}

void ft_list_clear(t_mlist **list)
{
	int n;

	if (!list || !*list)
		return ;
	n = 0;
	while ((*list)->argv[n])
	{
		free((*list)->argv[n]);
		n++;
	}
	free((*list)->argv);
	free((*list)->command);
	free((*list)->bin);
	*list = NULL;
}

void ft_free_2_linked_list(t_mlist **list)
{
	while (*list)
	{
		if ((*list)->next)
		{
			*list = (*list)->next;
			ft_list_clear(&(*list)->prev);
		}
		else
			ft_list_clear(list);
	}
}

void	ft_action(int sig)
{
	sig = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char **argv, char **env)
{
	(void) argv;
	argc = 0;
	ENV = env;


	char *str;
	signal(SIGINT, ft_action);
	rl_catch_signals = 0;
	using_history();
	while (1)
	{
		str = readline("minishell>$ ");
		if (!str || ft_strncmp("exit", str, 5) == 0)
			return (1);
		t_mlist *list = ft_fill_list(str);
		add_history(str);
		print_list(list);
		free(str);
		/* ft_pipex(list); */
		ft_free_2_linked_list(&list);
	}
	return (0);
}
