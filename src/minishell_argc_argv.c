/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:59:26 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:59:28 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_argc(char **arr)
{
	int	n;

	n = 0;
	if (*arr[0] == '|' || *arr[0] == '&' || *arr[0] == '>')
		arr++;
	while (*arr && *arr[0] != '|' && *arr[0] != '&' && *arr[0] != '>')
	{
		n++;
		arr++;
	}
	return (n);
}

char	**ft_argv(char **arr)
{
	char	**argv;
	char	**tmp;

	argv = (char **)malloc(sizeof(char *) * ft_argc(arr) + 1);
	tmp = argv;
	if (!argv)
		return (NULL);
	if (*arr[0] == '|' || *arr[0] == '&' || *arr[0] == '>' || *arr[0] == '<')
		arr++;
	while (*arr && *arr[0] != '|' && *arr[0] != '&' && *arr[0] != '>')
	{
		*argv = *arr;
		argv++;
		arr++;
	}
	*argv = NULL;
	return (tmp);
}
