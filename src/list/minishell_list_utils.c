/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:39 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/04 16:18:19 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_command(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp && (*tmp[0] == '>' || *tmp[0] == '<'))
	{
		if (*(tmp + 1))
			tmp += 2;
		else
			return (NULL);
	}
	return (*tmp);
}

t_mlist	*ft_list_new(t_shell *shell, char **argv, char *command)
{
	t_mlist	*new;
	char	*bin;

	bin = ft_find_command(argv);
	new = (t_mlist *)malloc(sizeof(t_mlist));
	new->bin = ft_get_absolute_path(shell, bin);
	new->argv = argv;
	new->command = command;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->isheredoc = 0;
	new->isoutput = 0;
	new->isinput = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_mlist	*ft_list_last(t_mlist *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_list_add_front(t_mlist **list, t_mlist *new)
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

void	ft_list_add_back(t_mlist **list, t_mlist *new)
{
	t_mlist	*tmp;

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
