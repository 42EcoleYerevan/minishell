/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:14:27 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/31 19:04:01 by agladkov         ###   ########.fr       */
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
			printf("argv \t: %s\n", (list->argv[n]));
			n++;
		}
		if (list->argv[0] == NULL)
			printf("argv \t: %s\n", NULL);
		printf("command\t: %s\n\n", (list->command));
		list = list->next;
	}
}

int main(int argc, char **argv, char **env)
{
	(void) argv;
	ENV = env;
	argc = 0;
	(void) argv;

	char *str;
	str = readline("minishel>$ ");
	t_mlist *list = ft_fill_list(str);
	print_list(list);
	ft_pipex(list);

	return (0);
}
