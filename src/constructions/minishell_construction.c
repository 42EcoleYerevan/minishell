/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_construction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:56:05 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/05 17:06:45 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_env(t_shell *shell, char *str)
{
	int		len;
	char	*value;

	len = 0;
	while (*str)
	{
		if (*str == '$')
		{
			value = ft_get_env_value_by_name(shell, str + 1);
			if (!value)
				value = ft_strdup("");
			len += ft_strlen(value);
			str += ft_len_env_key(str + 1) + 1;
			free(value);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

static void	ft_insert_str(t_shell *shell, char *dst, char *src)
{
	char	*value;

	while (*src)
	{
		if (*src == '$' && *(src + 1) != '\0')
		{
			value = ft_get_env_value_by_name(shell, src + 1);
			if (!value)
				value = ft_strdup("");
			ft_strlcpy(dst, value, ft_strlen(value) + 1);
			dst += ft_strlen(value);
			src += ft_len_env_key(src + 1) + 1;
			free(value);
		}
		else
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
	*dst = '\0';
}

char	*ft_set_env(t_shell *shell, char *str)
{
	int		len;
	char	*out;

	if (!str)
		return (NULL);
	if (ft_strchr(str, '$') == 0)
		out = ft_strdup(str);
	else
	{
		len = ft_len_env(shell, str);
		out = (char *)malloc(sizeof(char) * (len + 1));
		if (!out)
			return (NULL);
		ft_insert_str(shell, out, str);
	}
	free(str);
	return (out);
}

static char	**ft_set_commands(t_shell *shell, char *str, char **out)
{
	int	n;

	if (!out)
		return (NULL);
	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		out[n] = ft_substr(str, 0, ft_len_command(str));
		if (ft_strchr(out[n], '\'') || ft_strchr(out[n], '\"'))
			out[n] = ft_parse_quotes(shell, out[n]);
		else
			out[n] = ft_set_env(shell, out[n]);
		str += ft_len_command(str);
		if (!out[n])
		{
			ft_free_2d_array_with_null(out);
			return (NULL);
		}
		str += ft_len_spaces(str);
		n++;
	}
	out[n] = NULL;
	return (out);
}

char	**ft_parse_construction(t_shell *shell, char *str)
{
	char	**out;
	int		len;

	len = ft_amount_commands(str) + 1;
	out = (char **)malloc(sizeof(char *) * len);
	out = ft_set_commands(shell, str, out);
	if (!out)
		return (NULL);
	return (out);
}
