/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:55 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/11 13:10:44 by agladkov         ###   ########.fr       */
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
