/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_create_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:18:09 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:18:10 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*ft_create_list(t_shell *shell, char **tokens)
{
	int		n;
	t_mlist	*list;

	n = 0;
	list = NULL;
	while (tokens[n])
	{
		ft_list_add_back(&list, ft_create_list_node(shell, tokens + n));
		n += ft_length_construction(tokens + n);
	}
	return (list);
}

t_mlist	*ft_create_list_node(t_shell *shell, char **tokens)
{
	t_mlist	*new;
	char	**argv;
	int		len;

	len = ft_token_count_in_construction(tokens);
	argv = ft_slice_arr(tokens, 0, len);
	ft_set_env_token(shell, argv);
	new = ft_list_new(shell, argv, ft_strdup(ft_find_token(tokens, "|")));
	return (new);
}
