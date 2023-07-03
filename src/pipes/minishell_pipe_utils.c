#include "minishell.h"

void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}


void ft_dup_pipe(t_mlist *list)
{
	if (list->next)
	{
		dup2(list->fd[1], 1);
		ft_close_pipe(list->fd);
	}
	if (list->prev)
	{
		dup2(list->prev->fd[0], 0);
		ft_close_pipe(list->prev->fd);
	}
}

void ft_close_fd(t_mlist *list)
{
	if (list->next)
		close(list->fd[1]);
	if (list->prev)
		ft_close_pipe(list->prev->fd);
}

