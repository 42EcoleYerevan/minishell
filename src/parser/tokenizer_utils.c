/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:20:57 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:23:12 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_token(char **tokens, char *str)
{
	int	n;
	int	len_token;

	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		len_token = ft_len_token(str);
		tokens[n] = ft_substr(str, 0, len_token);
		str += len_token;
		str += ft_len_spaces(str);
		n++;
	}
	tokens[n] = NULL;
}

int	ft_token_count(char *str)
{
	int	n;

	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		str += ft_len_token(str);
		str += ft_len_spaces(str);
		n++;
	}
	return (n);
}

int	ft_len_token(char *str)
{
	if (ft_is_separator(str))
		return (ft_len_separator(str));
	else
		return (ft_len_word(str));
}

int	ft_is_separator(char *str)
{
	const char	*separators;

	separators = "|<>";
	if (ft_strchr(separators, *str) == NULL)
		return (0);
	return (1);
}
