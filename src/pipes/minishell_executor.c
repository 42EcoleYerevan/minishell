/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:53:14 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/19 18:20:00 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(char **env)
{
	ft_free_2d_array_with_null(env);
	free(env);
}

static int	ft_check_argument(t_mlist *list)
{
	DIR	*d;

	if (!list->bin)
	{
		d = opendir(list->argv[0]);
		if (list->argv && d)
		{
			closedir(d);
			printf("minishell: %s: is a directory\n", list->argv[0]);
			return (126);
		}
		else if (list->argv && list->argv[0])
			return (ft_print_error(list));
	}
	return (0);
}

void	ft_check(int status, int check, char **env)
{
	if (status != 0 || check != 0)
	{
		ft_free_env(env);
		if (check != 0)
			exit(check);
		exit(status);
	}
}

int	ft_executor(t_shell *shell, t_mlist *list)
{
	char	**env;
	int		status;
	int		check;

	env = ft_env_to_arr(shell->env, 0, -1);
	status = ft_handle_redirect(shell, list);
	check = ft_check_argument(list);
	ft_define_signals();
	ft_delete_qoute_in_argv(list->argv);
	if (fork() == 0)
	{
		ft_check(status, check, env);
		ft_dup_pipe(list);
		ft_dup_redirect(list);
		ft_close_fd(list);
		if (list->bin)
			exit(execve(list->bin, list->argv, env));
		exit(1);
	}
	ft_close_fd(list);
	ft_free_env(env);
	return (0);
}
