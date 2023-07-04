/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:42:44 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:43:12 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_rebase_redirect_argv(char ***argv, int n, int step, int len)
{
	if (n + step < len && (*argv)[n + step])
	{
		free((*argv)[n]);
		(*argv)[n] = (*argv)[n + step];
		(*argv)[n + step] = NULL;;
	}
	else 
	{
		if ((*argv)[n])
			free((*argv)[n]);
		(*argv)[n] = NULL;
	}
}

void ft_remove_redirect(char ***argv, int n)
{
	int	len;
	int	step;

	if ((*argv)[n + 1])
		step = 2;
	else
		step = 1;
	len = ft_len_nullable_2d_array(*argv);
	while (n < len)
	{
		ft_rebase_redirect_argv(argv, n, step, len);
		n ++;
	}
}

void	ft_dup_redirect(t_mlist *list)
{
	if (list->isinput)
	{
		dup2(list->heredoc[0], 0);
		close(list->heredoc[0]);
	}
	if (list->isoutput)
	{
		dup2(list->heredoc[1], 1);
		close(list->heredoc[1]);
	}
	if (list->isheredoc == 1)
	{
		dup2(list->heredoc[0], 0);
		ft_close_pipe(list->heredoc);
	}
}
