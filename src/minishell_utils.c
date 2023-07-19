/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:08:48 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:14:09 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_qoute_in_argv(char **argv)
{
	int	n;

	n = 0;
	while (argv[n])
	{
		argv[n] = ft_delete_quotes(argv[n]);
		argv++;
	}
}
