/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:13:56 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/17 12:53:16 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_wait_pid(void)
{
	pid_t	wpid;
	pid_t	tmp;
	int		status;

	tmp = 0;
	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid > tmp)
		{
			if (status >= 256)
				exit_status = status / 256;
			tmp = wpid;
		}
		wpid = waitpid(-1, &status, 0);
	}
}

int	ft_print_error(t_mlist *list)
{
	if (list->argv[0] || list->bin)
	{
		printf("minishell: %s: command not found\n", list->argv[0]);
		return (127);
	}
	else
		return (ft_redirect_unexpected_error(list->command));
}

void	executor(t_shell *shell)
{
	t_mlist	*tmp;

	tmp = *shell->list;
	while (tmp)
	{
		if (tmp->next)
			pipe(tmp->fd);
		if (ft_isbuiltin(tmp->bin) || ft_isbuiltin(tmp->argv[0]))
			exit_status = ft_builtin_handler(shell, tmp);
		else if (tmp && !tmp->argv[0] && !tmp->bin && tmp->command)
		{
			exit_status = ft_redirect_unexpected_error(tmp->command);
			return ;
		}
		else
			exit_status = ft_executor(shell, tmp);
		tmp = tmp->next;
	}
	ft_wait_pid();
}

int exit_status;

void	ft_event_loop(t_shell *shell)
{
	char	*str;
	t_mlist	*list;

	while (1)
	{
		/* ft_init_action(); */
		str = readline("minishell>$ ");
		if (str && *str == '\0')
		{
			free(str);
			continue ;
		}
		ctrl_d_handler(str);
		add_history(str);
		list = ft_parser(shell, str);
		shell->list = &list;
		exit_status = ft_is_valid_linked_list(list);
		if (exit_status == 0)
			executor(shell);
		free(str);
		ft_free_2_linked_list(shell->list);
	}
}

int	main(int argc, char **argv, char **menv)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->env = ft_create_envlist(menv);
	(void) argv;
	(void) menv;
	if (argc == 1)
	{
		shell = (t_shell *)malloc(sizeof(t_shell));
		shell->env = ft_create_envlist(menv);
		rl_catch_signals = 0;
		using_history();
		ft_event_loop(shell);
	}
	return (exit_status);
}
