/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:08:48 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/11 17:58:36 by agladkov         ###   ########.fr       */
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

int	ft_is_valid_linked_list(t_mlist *list)
{
	int	n;
	int	redirect_error;
	int	pipe_error;

	while (list)
	{
		n = 0;
		pipe_error = ft_check_pipe_error(list);
		if (pipe_error)
			return (pipe_error);
		while (list->argv[n])
		{
			redirect_error = ft_check_redirect_error(list, n);
			if (redirect_error)
				return (redirect_error);
			n++;
		}
		list = list->next;
	}
	return (0);
}
