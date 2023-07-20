/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:00:56 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/20 14:03:06 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_node_del(t_env **node)
{
	if (!(*node))
		return ;
	if ((*node)->key)
		free((*node)->key);
	(*node)->key = NULL;
	if ((*node)->value)
		free((*node)->value);
	(*node)->value = NULL;
	free(*node);
	node = NULL;
}

void	ft_unset_errprint(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	while (*arg)
		write(2, arg++, 1);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	ft_unset_valid(char *arg)
{
	int	status;
	int	i;

	i = 0;
	if (!arg)
		return (0);
	status = 0;
	if (ft_isdigit(arg[0]))
		status = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			status = 1;
			break ;
		}
		i++;
	}
	if (status == 1)
		ft_unset_errprint(arg);
	return (status);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_unset(char **args, t_env **env, int status)
{
	t_env	*tmp;
	t_env	*node;

	node = *env;
	while (*args)
	{
		if (ft_unset_valid(*args))
			status = 1;
		while (node->next)
		{
			if (!(ft_strcmp(*args, (*env)->key)))
					*env = ft_del_first(env);
			if (!ft_strcmp(node->next->key, *args))
			{
				tmp = node->next;
				node->next = tmp->next;
				ft_node_del(&tmp);
				break ;
			}
			node = node->next;
		}
		args++;
		node = *env;
	}
	return (status);
}
