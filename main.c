/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:14:27 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/23 18:25:44 by agladkov         ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"

void ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void ft_child(t_mlist *list)
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
	execve(list->bin, list->argv, ENV);
}

void ft_pipex(t_mlist *list)
{
	int pid;

	while (list)
	{
		if (list->command)
			pipe(list->fd);
		pid = fork();
		if (pid == 0)
		{
			if (list->next == NULL && list->prev == NULL)
				execve(list->bin, list->argv, ENV);
			else
				ft_child(list);
		}
		if (list->prev && list->prev->command)
			ft_close_pipe(list->prev->fd);
		list = list->next;
	}
	wait(NULL);
}

int main(int argc, char **argv, char **env)
{
	(void) argv;
	ENV = env;
	argc = 0;
	(void) argv;

	char *str;

	str = readline("minishel>$ ");
	t_mlist *list = ft_fill_list(str);
	ft_pipex(list);
	return (0);
}
