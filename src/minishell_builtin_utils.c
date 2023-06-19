/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:26:41 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 17:14:46 by almeliky         ###   ########.fr       */
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

void	ft_export_change(t_env *env, char *str)
{
	int	len;

	if (env == NULL)
		return ;
	if (env->value)
		free(env->value);
	if (*str == '=')
		str++;
	len = ft_strlen(str);
	env->value = malloc(len + 1);
	len = 0;
	while (*str)
		env->value[len++] = *str++;
	env->value[len] = '\0';
}

int	ft_find_env(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i == 0)
		return (0);
	while (env)
	{
		if (!ft_strncmp(str, env->key, i))
		{
			ft_export_change(env, str + i);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*ft_value_by_key(char *key, t_env *env)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(key, env->key, i))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_ptr_by_key(char *key, t_env *env)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(key, env->key, i))
			return (env);
		env = env->next;
	}
	return (NULL);
}
