/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:14:27 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/30 17:37:44 by agladkov         ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void) argv;
	ENV = env;
	argc = 0;
	(void) argv;

	char *str;
	str = readline("minishel>$ ");
	t_mlist *list = ft_fill_list(str);

	int n;
	while (list)
	{
		n = 0;
		while (list->argv[n])
		{
			puts(list->argv[n]);
			n++;
		}
		list = list->next;
	}
	/* ft_pipex(list); */
	return (0);
}
