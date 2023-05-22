/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:39 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/22 18:02:52 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist *ft_list_new(char **argv, char *command)
{
	t_mlist *new;

	new = (t_mlist *)malloc(sizeof(t_mlist));
	new->argv = argv;
	new->command = command;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_mlist *ft_list_last(t_mlist *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void ft_list_add_front(t_mlist **list, t_mlist *new)
{
	if (!new || !list || !*list)
		return ;
	if (!*list)
	{
		*list = new;
		(*list)->prev = NULL;
		(*list)->next = NULL;
	}
	else
	{
		(*list)->prev = new;
		new->next = *list;
		*list = new;
		new->prev = NULL;
	}
}

void ft_list_add_back(t_mlist **list, t_mlist *new)
{
	t_mlist *tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		(*list)->next = NULL;
		(*list)->prev = NULL;
	}
	else
	{
		tmp = ft_list_last(*list);
		new->prev = tmp;
		tmp->next = new;
	}
}

void ft_list_clear(t_mlist **list)
{
	int n;

	if (!list || !*list)
		return ;
	n = 0;
	while ((*list)->argv[n])
	{
		free((*list)->argv[n]);
		n++;
	}
	free((*list)->argv);
	free((*list)->command);
	free(list);
	*list = NULL;
}
