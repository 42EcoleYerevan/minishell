/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_construction_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:56:11 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/07 12:49:20 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_num_quotes(char *str)
{
	int	num;

	num = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			num++;
		str++;
	}
	return (num);
}

char	*ft_delete_quotes(char *str)
{
	char	*tmp;
	char	*out;
	int		indx;
	int		len;

	len = ft_strlen(str) - ft_num_quotes(str) + 1;
	out = (char *)malloc(sizeof(char) * len);
	if (!out)
	{
		free (str);
		return (NULL);
	}
	indx = 0;
	tmp = str;
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
			out[indx++] = *str;
		str++;
	}
	out[indx] = 0;
	free(tmp);
	return (out);
}

void	ft_change_element_with_free(t_shell *shell, char **out, int n)
{
	char *tmp;

	if (ft_strchr(out[n], '\'') || ft_strchr(out[n], '\"'))
	{
		tmp = ft_parse_quotes(shell, out[n]);
		free(out[n]);
		out[n] = tmp;
	}
	else
	{
		tmp = ft_set_env(shell, out[n]);
		free(out[n]);
		out[n] = tmp;
	}
}
