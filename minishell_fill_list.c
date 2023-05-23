/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fill_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:59:28 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/23 13:33:41 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_set_list_command(t_mlist **list, char **argv, int n)
{
	if (argv[n][0] == '|' ||\
		argv[n][0] == '&' ||\
	   	argv[n][0] == '>' ||\
		argv[n][0] == '<')
	{
		ft_list_add_back(list, ft_list_new(argv, argv[n]));
		argv[n] = NULL;
	}
	else
		ft_list_add_back(list, ft_list_new(argv, NULL));
}

t_mlist *ft_fill_list(char *str)
{
	t_mlist *list;
	char *construction;
	char **argv;
	int n;

	while (*str)
	{
		construction = ft_substr(str, 0, ft_len_construction(str));
		argv = ft_parse_construction(construction);
		n = ft_len_commands(construction) - 1;
		ft_set_list_command(&list, argv, n);
		str += ft_len_construction(str);
	}
	return (list);
}
