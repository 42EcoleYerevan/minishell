/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:55 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/11 17:02:51 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_lowercase(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		*tmp = ft_tolower(*tmp);
		tmp++;
	}
	return (str);
}

char	**ft_echo_skip_flags(char **arr)
{
	int		i;
	char	*tmp;

	while (*arr)
	{
		i = 0;
		tmp = *arr;
		if (tmp[i] == '-')
		{
			i++;
			while (tmp[i] && tmp[i] == 'n')
				i++;
			if (tmp[i] != '\0')
				return (arr);
		}
		else
			return (arr);
		arr++;
	}
	return (arr);
}
