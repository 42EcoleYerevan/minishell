/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:45:32 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 19:46:06 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_print(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp("_", env->key, ft_strlen(env->key)))
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}

t_env	*ft_export_add(char *str)
{
	int		len;
	t_env	*newenv;

	newenv = (t_env *)malloc(sizeof(t_env));
	if (!newenv)
		return (NULL);
	len = ft_strlen(str);
	if (ft_strchr(str, '='))
	{
		len = ft_strlen(ft_strchr(str, '=') + 1);
		newenv->value = ft_substr(str, ft_strlen(str) - len, len);
		len = ft_strlen(str) - len - 1;
	}
	else
		newenv->value = NULL;
	newenv->key = malloc(len + 1);
	newenv->key[len] = '\0';
	while (len-- > 0)
		newenv->key[len] = str[len];
	newenv->next = NULL;
	return (newenv);
}

void	ft_export_errprint(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	while (*arg)
		write(2, arg++, 1);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	ft_export_concat(char *arg, t_env *env, int i)
{
	char	*prev;

	if (arg[i] == '+' && arg[i + 1] != '=')
		return (1);
	prev = ft_value_by_key(arg, env);
	if (!prev)
		prev = "";	
	ft_export_change(ft_ptr_by_key(arg, env), ft_strjoin(prev, (arg + i + 2)));
	return (2);
}

int	ft_export_valid(char *arg, int *res, t_env *env)
{
	int	status;
	int	i;
	
	i = 0;
	if (!arg)
		return (0);
	status = 0;
	if (ft_isdigit(arg[0]) || arg[0] == '=')
		status = 1;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			status = 1;
			break ;
		}
		i++;
	}
	if (arg[i] == '+')
		status = ft_export_concat(arg, env, i);
	*res = status;
	if (status == 1)
		ft_export_errprint(arg);
	return (status);
}