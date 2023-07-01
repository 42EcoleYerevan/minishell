/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:51:27 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:52:11 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_redirect(t_mlist *list)
{
	int	n;
	int	out;

	n = 0;
	out = 0;
	while (list->argv[n])
	{
		if (list->argv[n][0] == '<')
			out = ft_redirect_input(list, n);
		else if (list->argv[n][0] == '>')
			out = ft_redirect_output(list, n);
		else
			n++;
	}
	return (out);
}
