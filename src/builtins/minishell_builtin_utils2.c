/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:55 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/20 14:03:29 by almeliky         ###   ########.fr       */
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

t_env	*ft_del_first(t_env **node)
{
	t_env	*tmp;

	tmp = *node;
	*node = (*node)->next;
	ft_node_del(&tmp);
	return (*node);
}
