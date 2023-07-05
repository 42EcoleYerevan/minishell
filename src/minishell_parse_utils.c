/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:56:39 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/05 16:59:53 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	out = ft_substr(str, 0, ft_len_quote(str, *str));
	if (*str == '\"')
	{
		out = ft_strtrim(out, "\"");
		out = ft_set_env(shell, out);
	}
	else
		out = ft_strtrim(out, "\'");
	return (out);
}

char	*ft_parse_quotes(t_shell *shell, char *str)
{
	char	*out;
	char	*tmp;

	out = "";
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
		{
			tmp = ft_substr(str, 0, ft_len_before_quote(str));
			str += ft_strlen(tmp);
			tmp = ft_set_env(shell, tmp);
		}
		else
		{
			tmp = ft_process_quote(shell, str);
			str += ft_len_quote(str, *str);
		}
		out = ft_strjoin(out, tmp);
		free(tmp);
		tmp = NULL;
	}
	return (out);
}

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
