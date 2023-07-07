/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:50:06 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/07 15:10:11 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_unexpected_error(char *command)
{
	printf("syntax error near unexpected token `%s`\n", command);
	rl_on_new_line();
	return (258);
}

int	ft_redirect_error_argument(t_mlist *list, int n)
{
	if (list->argv[n + 1])
		return (ft_redirect_unexpected_error(list->argv[n + 1]));
	else
	{
		if (list->command)
			return (ft_redirect_unexpected_error(list->command));
		return (ft_redirect_unexpected_error("newline"));
	}
}
