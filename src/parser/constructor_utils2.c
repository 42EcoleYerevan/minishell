/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:18:31 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:21:22 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_element_with_free(t_shell *shell, char **out, int n)
{
	char	*tmp;

	if (ft_strchr(out[n], '\'') || ft_strchr(out[n], '\"'))
	{
		tmp = ft_parse_quotes(shell, out[n]);
		free(out[n]);
		out[n] = tmp;
	}
	else
	{
		tmp = ft_set_env(shell, out[n]);
		free(out[n]);
		out[n] = tmp;
	}
}
