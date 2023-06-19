/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:00:56 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 19:46:45 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_unset(char **args, t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	printf("unset here\n");
	if (!(*args))
		return (0);
	node = *env;
	while (*args)
	{
		while (node->next)
		{
			if (!ft_strncmp(node->next->key, *args, ft_strlen(*args)))
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
	return (0);
}