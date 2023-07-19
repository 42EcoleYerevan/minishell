/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:20:27 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:20:34 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*ft_parser(t_shell *shell, char *str)
{
	char	**tokens;
	t_mlist	*list;

	tokens = ft_tokenizer(str);
	list = ft_constructor(shell, tokens);
	ft_free_2d_array_with_null(tokens);
	free(tokens);
	return (list);
}
