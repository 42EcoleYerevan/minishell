/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:52:30 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:53:04 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_dup_pipe(t_mlist *list)
{
	if (list->next)
	{
		dup2(list->fd[1], 1);
		close(list->fd[1]);
	}
	if (list->prev)
	{
		dup2(list->prev->fd[0], 0);
		close(list->prev->fd[0]);
	}
}

void	ft_close_fd(t_mlist *list)
{
	if (list->next)
		close(list->fd[1]);
	if (list->prev)
		close(list->prev->fd[0]);
}
