/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:00:12 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 19:45:50 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (i > 0 && key[i - 1] == '+')
		i--;
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
	if (i > 0 && key[i - 1] == '+')
		i--;
	while (env)
	{
		if (!ft_strncmp(key, env->key, i))
			return (env);
		env = env->next;
	}
	return (NULL);
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
		if ((ft_find_env(*args, *env) && *args) || ft_export_valid(*args, &res, *env))
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