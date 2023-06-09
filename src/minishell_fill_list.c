/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fill_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:59:28 by agladkov          #+#    #+#             */
/*   Updated: 2023/06/02 16:10:19 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void ft_set_list_command(t_shell *shell,
								t_mlist **list,
								char **argv,
								int n)
{
	if (argv[n][0] == '|' ||\
		argv[n][0] == '&' ||\
	   	argv[n][0] == '>' ||\
		argv[n][0] == '<')
	{
		ft_list_add_back(list, ft_list_new(shell, argv, argv[n]));
		argv[n] = NULL;
	}
	else
		ft_list_add_back(list, ft_list_new(shell, argv, NULL));
}

t_mlist *ft_fill_list(t_shell *shell, char *str)
{
	t_mlist *list;
	char *construction;
	char **argv;
	int n;

	list = NULL;
	while (*str)
	{
		construction = ft_substr(str, 0, ft_len_construction(str));
		argv = ft_parse_construction(shell, construction);
		n = ft_amount_commands(construction) - 1;
		ft_set_list_command(shell, &list, argv, n);
		str += ft_len_construction(str);
	}
	return (list);
}
