/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_len_construction.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:55:58 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:56:00 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_construction(char *str)
{
	int	n;

	n = 0;
	while (*str
		&& *str != '|'
		&& *str != '&'
		&& *str != ';')
	{
		n++;
		str++;
	}
	n += ft_len_separator(str);
	str += ft_len_separator(str);
	n += ft_len_spaces(str);
	return (n);
}

int	ft_amount_constructions(char *str)
{
	int	n;

	n = 0;
	while (*str)
	{
		n++;
		str += ft_len_construction(str);
	}
	return (n);
}
