/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:58:18 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/11 17:12:33 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "libft/libft.h"

char	*ft_get_env_value_by_name(t_shell *shell, char *name)
{
	char	*tmp;
	char	*out;

	if (*name == '\0')
		return (ft_strdup("$"));
	if (*name == '?')
		return (ft_itoa(exit_status));
	tmp = ft_substr(name, 0, ft_len_env_key(name));
	out = ft_get_env_value(shell, tmp);
	free(tmp);
	return (out);
}

char	*ft_get_env_value(t_shell *shell, char *var)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp && ft_strncmp(tmp->key, var, ft_strlen(var) + 1) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	**ft_env_to_arr(t_env *env, int len, int i)
{
	t_env	*start;
	char	**arr;
	char	*tmp;

	start = env;
	while (env && ++len)
		env = env->next;
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = NULL;
	while (start && ++i >= 0)
	{
		arr[i] = NULL;
		if (start->value)
			arr[i] = ft_strjoin("=", start->value);
		tmp = arr[i];
		arr[i] = ft_strjoin(start->key, arr[i]);
		free(tmp);
		start = start->next;
	}
	len = 0;
	return (arr);
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
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (0);
}
