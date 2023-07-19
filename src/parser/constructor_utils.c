/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:15:24 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:18:25 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_slice_arr(char **arr, int start, int end)
{
	char	**out;
	int		n;

	out = (char **)malloc(sizeof(char *) * (end - start + 1));
	n = 0;
	while (start < end)
	{
		out[n] = ft_substr(arr[start], 0, ft_strlen(arr[start]));
		start++;
		n++;
	}
	out[n] = NULL;
	return (out);
}

char	*ft_find_token(char **tokens, char *token)
{
	int	n;

	n = 0;
	while (tokens[n] && \
			ft_strncmp(tokens[n], token, ft_strlen(token) + 1) != 0)
		n++;
	return (tokens[n]);
}

int	ft_length_construction(char **tokens)
{
	int	n;

	n = ft_token_count_in_construction(tokens);
	if (tokens[n])
		n++;
	return (n);
}

int	ft_token_count_in_construction(char **tokens)
{
	int	n;

	n = 0;
	while (tokens[n])
	{
		if (tokens[n][0] == '|')
			return (n);
		n++;
	}
	return (n);
}

void	ft_set_env_token(t_shell *shell, char **tokens)
{
	int	n;

	n = 0;
	while (tokens[n])
	{
		ft_change_element_with_free(shell, tokens, n);
		n++;
	}
}
