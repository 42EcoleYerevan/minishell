/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:59:14 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 18:59:19 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, int n)
{
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		args++;
		if (*args)
			write (1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}