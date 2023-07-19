/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:15:12 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:15:13 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_before_quote(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str && *str != '\'' && *str != '\"')
		str++;
	return (str - tmp);
}

static char	*ft_process_quote(t_shell *shell, char *str)
{
	char	*out;
	char	*tmp;

	tmp = ft_substr(str, 0, ft_len_quote(str, *str));
	if (*str == '\"')
		out = ft_set_env(shell, tmp);
	else
		out = ft_strdup(tmp);
	free(tmp);
	return (out);
}

static char	*ft_parse_strjoin(char *str1, char *str2)
{
	char	*tmp;
	char	*out;

	tmp = str1;
	if (str1 == NULL)
		str1 = "";
	out = ft_strjoin(str1, str2);
	free(tmp);
	free(str2);
	return (out);
}

char	*ft_parse_quotes(t_shell *shell, char *str)
{
	char	*out;
	char	*tmp;
	char	*tmp2;

	out = NULL;
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
		{
			tmp = ft_substr(str, 0, ft_len_before_quote(str));
			str += ft_strlen(tmp);
			tmp2 = tmp;
			tmp = ft_set_env(shell, tmp);
			free(tmp2);
		}
		else
		{
			tmp = ft_process_quote(shell, str);
			str += ft_len_quote(str, *str);
		}
		out = ft_parse_strjoin(out, tmp);
		tmp = NULL;
	}
	return (out);
}
