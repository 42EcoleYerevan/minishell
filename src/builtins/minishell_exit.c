/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:59:01 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 19:46:23 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_num_check(char *arg)
{
	int					i;
	unsigned long long	max;
	unsigned long long	check;

	max = 9223372036854775807;
	i = 0;
	if (*arg == '-' || *arg == '+')
		arg++;
	if (ft_strlen(arg) > 19)
		return (1);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	check = 0;
	i = 0;
	while (arg[i])
	{
		check *= 10;
		check += arg[i] - '0';
		i++;
	}
	return (check > max);
}

int	ft_exit(char **args)
{
	if (!args || !args[0])
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (ft_num_check(args[0]))
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	else if (args[1])
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	ft_putendl_fd("exit", 1);
	exit(ft_atoi(args[0]));
	return (0);
}
