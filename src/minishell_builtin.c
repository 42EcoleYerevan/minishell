/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 20:27:33 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/11 20:27:33 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

int	ft_echo(char **args, int n)
{
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		args++;
		if (*args)
			write (1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}

int	ft_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(env->key, 1);
		write(1, "=", 1);
		ft_putstr_fd(env->value, 1);
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
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

int	ft_export(char **args, t_env **env)
{
	int		res;
	t_env	*last;

	res = 0;
	if (args[0] == NULL)
		return (ft_export_print(*env));
	last = *env;
	while (last->next)
		last = last->next;
	while (*args)
	{
		if ((ft_find_env(*args, *env) && *args) || ft_export_valid(*args, &res))
		{
			args++;
			continue ;
		}
		last->next = ft_export_add(*args);
		if (last->next)
			last = last->next;
		if (!last)
			res = 1;
		args++;
	}
	return (res);
}
