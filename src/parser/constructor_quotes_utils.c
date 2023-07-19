/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_quotes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:19:36 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:20:19 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_without_quotes(char *str)
{
	int	n;

	n = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			n += ft_len_between_quotes(str);
			str += ft_len_quote(str, *str);
		}
		else
		{
			n++;
			str++;
		}
	}
	return (n);
}

int	ft_len_between_quotes(char *str)
{
	int	n;

	if (*str != '\'' && *str != '\"')
		return (0);
	n = ft_len_quote(str, *str);
	return (n - 2);
}

void	ft_copy_between_quotes(char *dst, char *src)
{
	char	quote;

	if (*src != '\'' && *src != '\"')
		return ;
	quote = *src++;
	while (*src && *src != quote)
		*dst++ = *src++;
}

void	ft_delete_quotes_loop(char *str, char *out)
{
	int		indx;

	indx = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			ft_copy_between_quotes(out + indx, str);
			indx += ft_len_between_quotes(str);
			str += ft_len_quote(str, *str);
		}
		else
		{
			out[indx] = *str;
			str++;
			indx++;
		}
	}
	out[indx] = '\0';
}

char	*ft_delete_quotes(char *str)
{
	char	*out;
	int		len;

	len = ft_len_without_quotes(str);
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
	{
		free (str);
		return (NULL);
	}
	ft_delete_quotes_loop(str, out);
	free(str);
	return (out);
}
