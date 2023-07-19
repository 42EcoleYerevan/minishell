/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:15:05 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:15:06 by agladkov         ###   ########.fr       */
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
		if (*src == '$' && *(src + 1) != '\0' && *(src + 1) != '\'' && \
				*(src + 1) != '\"')
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
	return (out);
}
