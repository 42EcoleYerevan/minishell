/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:43:26 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:44:54 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/fcntl.h>

int	ft_redirect_two_output(t_mlist *list, int n)
{
	int	out;

	out = ft_check_next_redirect_input_argument(list, n);
	if (out == 0)
		list->heredoc[1] = open(list->argv[n + 1],
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (out);
}

int	ft_redirect_one_output(t_mlist *list, int n)
{
	int	out;

	out = ft_check_next_redirect_input_argument(list, n);
	if (out == 0)
		list->heredoc[1] = open(list->argv[n + 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (out);
}

int	ft_redirect_output(t_mlist *list, int n)
{
	int	out;

	if (ft_strncmp(list->argv[n], ">", ft_strlen(list->argv[n]) + 1) == 0)
		out = ft_redirect_one_output(list, n);
	else
		out = ft_redirect_two_output(list, n);
	ft_remove_redirect(&list->argv, n);
	if (out == 0)
		list->isoutput = 1;
	return (out);
}
