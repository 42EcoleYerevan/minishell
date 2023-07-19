/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_construction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:56:05 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/19 12:44:24 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_set_commands(t_shell *shell, char *str, char **out)
{
	int	n;

	if (!out)
		return (NULL);
	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		out[n] = ft_substr(str, 0, ft_len_command(str));
		str += ft_len_command(str);
		ft_change_element_with_free(shell, out, n);
		if (!out[n])
		{
			ft_free_2d_array_with_null(out);
			return (NULL);
		}
		str += ft_len_spaces(str);
		n++;
	}
	out[n] = NULL;
	return (out);
}

char	**ft_parse_construction(t_shell *shell, char *str)
{
	char	**out;
	int		len;

	len = ft_amount_commands(str) + 1;
	out = (char **)malloc(sizeof(char *) * len);
	out = ft_set_commands(shell, str, out);
	if (!out)
		return (NULL);
	return (out);
}
