/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:53:14 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 20:53:50 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_executor(t_shell *shell, t_mlist *list)
{
	char	**env;
	int		status;

	env = ft_env_to_arr(shell->env, 0, -1);
	status = ft_handle_redirect(list);
	if (status != 0)
		return (status);
	if (fork() == 0)
	{
		ft_dup_pipe(list);
		ft_close_fd(list);
		ft_dup_redirect(list);
		if (list->bin)
			return execve(list->bin, list->argv, env);
		exit(0);
	}
	ft_close_fd(list);
	ft_free_2d_array_with_null(env);
	free(env);
	return (0);
}
