/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fill_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:59:28 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/11 19:30:38 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_list_command(t_shell *shell,
								t_mlist **list,
								char **argv,
								int n)
{
	if (argv[n][0] == '|'
		|| argv[n][0] == '&')
	{
		ft_list_add_back(list, ft_list_new(shell, argv, argv[n]));
		argv[n] = NULL;
	}
	else
		ft_list_add_back(list, ft_list_new(shell, argv, NULL));
}

int	ft_len_nullable_2d_array(char **arr)
{
	int	n;

	n = 0;
	if (!arr)
		return (0);
	while (arr[n])
		n++;
	return (n);
}

int	ft_check_unclosed_quotes(char *str)
{
	int	check;

	if (*str == '\0')
		return (0);
	check = 0;
	while (*str)
	{
		str += ft_len_before_quote(str);
		if (*str == '\'' || *str == '\"')
			check = ft_len_quote(str, *str);
		if (check == -1)
		{
			printf("minishell: syntax error: unclosed quotes\n");
			exit_status = 1;
			return (1);
		}
		str += check;
	}
	return (0);
}

t_mlist	*ft_fill_list(t_shell *shell, char *str)
{
	t_mlist	*list;
	char	*construction;
	char	**argv;
	int		n;

	list = NULL;
	while (*str)
	{
		if (ft_check_unclosed_quotes(str))
			return (NULL);
		construction = ft_substr(str, 0, ft_len_construction(str));
		argv = ft_parse_construction(shell, construction);
		n = ft_amount_commands(construction) - 1;
		free(construction);
		if (n == -1)
			return (NULL);
		ft_set_list_command(shell, &list, argv, n);
		str += ft_len_construction(str);
	}
	return (list);
}
