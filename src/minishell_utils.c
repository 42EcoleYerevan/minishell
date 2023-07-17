/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:08:48 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/18 00:56:20 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redirect_error(t_mlist *list, int n)
{
	int	error;

	error = 0;
	if (ft_strncmp(list->argv[n], "<", 2) == 0)
		error = ft_check_one_redirect_input_argument(list, n);
	else if (list->argv[n][0] == '>' || \
			ft_strncmp(list->argv[n], "<<", 3) == 0)
		error = ft_check_next_redirect_input_argument(list, n);
	return (error);
}

int	ft_check_pipe_error(t_mlist *list)
{
	if (list->command && !list->bin && !list->argv[0])
	{
		if (list->next && list->next->command)
			return (ft_redirect_unexpected_error(list->command));
		else if (list->next && list->next->argv[0])
			return (ft_redirect_unexpected_error(list->next->argv[0]));
	}
	return (0);
}

int ft_check_quotes_in_string(char *str)
{
	int i;
	int	len;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			len = ft_len_quote(str + i, str[i]);
			if (len == -1)
				return (1);
			i += len;
		}
		else
			i++;
	}
	return (0);
}

int	ft_check_unclosed_quotes_in_argv(char **argv)
{
	int	n;

	n = 0;
	while (argv[n])
	{
		if (ft_check_quotes_in_string(argv[n]))
			return (1);
		n++;
	}
	return (0);
}

int	ft_is_valid_argv(t_mlist *list)
{
	int	error;
	int	n;

	n = 0;
	while (list->argv[n])
	{
		error = ft_check_unclosed_quotes_in_argv(list->argv);
		if (error)
			return (error);
		error = ft_check_redirect_error(list, n);
		if (error)
			return (error);
		n++;
	}
	return (0);
}

int	ft_is_valid_linked_list(t_mlist *list)
{
	int	error;

	if (!list)
		return (1);
	while (list)
	{
		error = ft_is_valid_argv(list);
		if (error)
			return (error);
		error = ft_check_pipe_error(list);
		if (error)
			return (error);
		list = list->next;
	}
	return (0);
}
