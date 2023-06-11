/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:35:17 by agladkov          #+#    #+#             */
/*   Updated: 2023/06/11 20:22:16 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	ft_child(t_mlist *list)
{
	if (list->command && list->prev == NULL)
	{
		dup2(list->fd[1], 1);
		close(list->fd[1]);
	}
	else if (list->command)
	{
		dup2(list->prev->fd[0], 0);
		dup2(list->fd[1], 1);
		ft_close_pipe(list->prev->fd);
	}
	else
	{
		dup2(list->prev->fd[0], 0);
		ft_close_pipe(list->prev->fd);
	}
	execve(list->bin, list->argv, NULL);
}

void	ft_pipex(t_mlist *list)
{
	int	pid;

	if (!list)
		return ;
	while (list)
	{
		if (list->command)
			pipe(list->fd);
		pid = fork();
		if (pid == 0)
		{
			if (list->next == NULL && list->prev == NULL && list->bin != NULL)
				execve(list->bin, list->argv, NULL);
			else if (list->bin != NULL
				&& ft_strncmp(list->command, "|", 2) == 0)
				ft_child(list);
			else
			{
				printf("minishell: %s command not found\n", list->argv[0]);
				exit(0);
			}
		}
		if (list->prev && list->prev->command)
			ft_close_pipe(list->prev->fd);
		list = list->next;
	}
	while (wait(NULL) != -1)
		;
}
