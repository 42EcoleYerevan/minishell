/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:56:39 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/19 12:42:45 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_env_key(char *str)
{
	int		len;
	char	*sep;

	sep = " <>|&./?@#$%^*-=+,[]{}\'\"";
	len = 0;
	if (*str == '?')
		return (1);
	while (str[len] && ft_strchr(sep, str[len]) == 0)
		len++;
	return (len);
}
