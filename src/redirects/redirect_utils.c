#include "minishell.h"

void ft_remove_redirect(char ***argv, int n)
{
	int	len;
	int step;

	if ((*argv)[n + 1])
		step = 2;
	else
		step = 1;
	len = ft_len_nullable_2d_array(*argv);
	while (n < len)
	{
		if (n + step < len && (*argv)[n + step])
			(*argv)[n] = (*argv)[n + step];
		else 
			(*argv)[n] = NULL;
		n++;
	}
}

void ft_dup_redirect(t_mlist *list)
{
	if (list->ispipe == 1)
	{
		dup2(list->fd[0], 0);
		ft_close_pipe(list->fd);
	}
	else
	{
		if (list->isinput )
		{
			dup2(list->fd[0], 0);
			close(list->fd[0]);
		}
		if (list->isoutput)
		{
			dup2(list->fd[1], 1);
			close(list->fd[1]);
		}
	}
}
