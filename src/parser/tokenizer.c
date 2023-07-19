/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:20:50 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:20:54 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tokenizer(char *str)
{
	char	**tokens;
	int		n;

	if (!str || *str == '\0')
		return (NULL);
	n = ft_token_count(str);
	tokens = (char **)malloc(sizeof(char *) * (n + 1));
	if (!tokens)
		return (NULL);
	ft_split_token(tokens, str);
	return (tokens);
}
